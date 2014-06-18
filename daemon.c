#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// 5 Seconds = 5 million microseconds
#define PAUSEINTERVAL (5 * 1000000)

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

  // Now we need to get a new unique SID so we aren't an orphan
  // Remember our parent has died.
  if (setsid() < 0) {
    fprintf(logfile, "Could not set our SID: %d\n", errno);
    fflush(logfile);
    exit(errno);
  }

  // Change to a safe directory
  if (chdir("/") < 0) {
    fprintf(logfile, "Could not change directory to root: %d\n", errno);
    fflush(logfile);
    exit(errno);
  }

  // Close standard pipes
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  fprintf(logfile, "Successfully finished initialization.\n");
  fflush(logfile);
}

void run() {
  struct timeval time;
  gettimeofday(&time, NULL);

  long lastrun = time.tv_usec;
  long currenttime = 0;

  while (1) {
    // Get the current time (this is the start time)
    gettimeofday(&time, NULL);
    currenttime = time.tv_usec;

    // Do stuff
    fprintf(logfile, "Seconds: %lu\n", currenttime);
    fflush(logfile);

    // Sleep
    int timeelapsed = currenttime - lastrun;
    if (timeelapsed < PAUSEINTERVAL) usleep(PAUSEINTERVAL - timeelapsed);

    // Reset timer
    lastrun = currenttime;
  }
}

int main() {
  pid_t pid = fork();

  // Check to see if there was an error with the fork
  if (pid < 0) exit(1);

  // If we are the child, then we do the heavy lifting
  if (pid == 0) {
    init();
    run();
    exit(0);
  } else {
    // Elsewise, we are the parent and we want to exit gracefully
    exit(0);
  }
}
