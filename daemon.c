#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE* logfile;

void init() {
  // Change the umask so we can write to log files
  umask(0);

  // We should initialize and open log files here
  logfile = fopen("./creddit.log", "a");
  if (logfile == NULL) {
    printf("Failed to create file with error: %d\n", errno);
    exit(errno);
  }
}

void run() {
}

int main() {
  pid_t pid = fork();

  // Check to see if there was an error with the fork
  if (pid < 0) exit(1);

  // If we are the child, then we do the heavy lifting
  if (pid == 0) {
    init();
    run();
  }

  // Elsewise, we are the parent and we want to exit gracefully
  exit(0);
}
