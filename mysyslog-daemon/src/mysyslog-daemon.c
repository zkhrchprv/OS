#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

#define CONFIG_FILE "/etc/mysyslog/mysyslog.cfg"

volatile sig_atomic_t stop;

void handle_signal(int sig) {
    if (sig == SIGTERM || sig == SIGINT) {
        stop = 1;
    }
}

void daemonize() {
    pid_t pid, sid;

    // Fork the parent process
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask
    umask(0);

    // Create a new SID for the child process
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    // Change the current working directory
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void read_config(char* path, char* format, char* driver) {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        syslog(LOG_ERR, "Failed to open config file: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Example of simple config file parsing
    fscanf(file, "path=%s\nformat=%s\ndriver=%s\n", path, format, driver);
    fclose(file);
}

int main() {
    char path[256];
    char format[256];
    char driver[256];

    // Set up signal handling
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    // Daemonize the process
    daemonize();

    // Open the syslog
    openlog("mysyslog-daemon", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Daemon started");

    // Read the configuration
    read_config(path, format, driver);
    syslog(LOG_INFO, "Configuration: path=%s, format=%s, driver=%s", path, format, driver);

    // Main loop
    while (!stop) {
        // Log example message
        syslog(LOG_INFO, "Daemon is running");
        sleep(10); // Sleep for a while
    }

    syslog(LOG_INFO, "Daemon is stopping");
    closelog();

    return EXIT_SUCCESS;
}
