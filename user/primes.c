#include "kernel/types.h"
#include "user.h"

void sieve(int in) {
  int prime, x, p[2];
  if (!read(in, &prime, sizeof(int))) {
    close(in);
    return;
  }
  while (pipe(p)) {  // must after check prime
    sleep(1);
  }
  fprintf(1, "prime %d\n", prime);
  if (fork()) {
    close(p[0]);
    while (read(in, &x, sizeof(int))) {
      if (x % prime != 0) {
        write(p[1], &x, sizeof(int));
      }
    }
    close(in);
    close(p[1]);
    wait(0);  // prevent from outputting after the process exiting
  } else {
    close(in); // must close in, because this process also can use this pipe, if not close, the pipe will not be released
    close(p[1]);
    sieve(p[0]);
  }
}

int main(int argc, char *argv[]) {
  int mx = 35;
  if (argc == 2) {
    mx = atoi(argv[1]);
  }
  int p[2];
  pipe(p);  // 0: read 1: write
  if (fork()) {
    close(p[0]);
    for (int i = 2; i <= mx; i++) {
      write(p[1], &i, sizeof(int));
    }
    close(p[1]);
    wait(0);  // prevent from outputting after the process exiting
  } else {
    close(p[1]);
    sieve(p[0]);
  }
  exit(0);
}