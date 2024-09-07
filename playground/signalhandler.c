#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handle_signal(int signum) {
    printf("Caught signal %d\n", signum);
    // Here you can implement custom behavior
}

int main() {
    struct sigaction sa;

    // Set up the structure to specify the new action.
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0; // Or SA_RESTART

    // Block every signal during the handler
    sigemptyset(&sa.sa_mask);

    // Set up the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error in sigaction");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep the program running to test signal handling
    int counter = 20;
    while (counter--) {
        printf("Running...\n");
        sleep(2);
    }

    return 0;
}
