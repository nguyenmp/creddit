#include <stdlib.h>
#include <unistd.h>

void init() {
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
