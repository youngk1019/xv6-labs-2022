#include "kernel/types.h"
#include "user.h"
#define MAXN 20

int main(int argc, char *argv[]) {
  int pipe1[2], pipe2[2];
  pipe(pipe1), pipe(pipe2);  // 0: read 1: write
  char buf[MAXN];
  if (fork()) {  // father return child's pid, child return 0
    // father process
    close(pipe1[0]), close(pipe2[1]);
    write(pipe1[1], "ping", strlen("ping"));
    close(pipe1[1]);
    read(pipe2[0], buf, strlen("pong"));
    fprintf(1, "%d: received %s\n", getpid(), buf);
    close(pipe2[0]);
  } else {
    // child process
    close(pipe1[1]), close(pipe2[0]);
    read(pipe1[0], buf, strlen("ping"));
    fprintf(1, "%d: received %s\n", getpid(), buf);
    close(pipe1[0]);
    write(pipe2[1], "pong", strlen("pong"));
    close(pipe2[1]);
  }
  exit(0);
}