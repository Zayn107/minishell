#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_COMMANDS 3

int main() {
    int pipes[NUM_COMMANDS - 1][2]; // Array to hold pipes for communication between commands
    pid_t child_pids[NUM_COMMANDS]; // Array to hold child process IDs

    // Create pipes
    for (int i = 0; i < NUM_COMMANDS - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork child processes
    for (int i = 0; i < NUM_COMMANDS; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            // Redirect input for all but the first child
			//zk redirect previous pipe to stdin, except first
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]); // Close read end of previous pipe
            }
            // Redirect output for all but the last child
            if (i < NUM_COMMANDS - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]); // Close write end of current pipe
            }
            // Close all other pipes
			//zk close all future and past pipes, just not current and last pipe
            for (int j = 0; j < NUM_COMMANDS - 1; j++) {
                if (j != i - 1 && j != i) {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }
            // Execute command using execve (replace with your desired command)
            char *args[] = {"/bin/ls", "-l", NULL};
            execve(args[0], args, NULL);
            // If execve fails
            perror("execve");
            exit(EXIT_FAILURE);
        }
		else
		{ // Parent process
            child_pids[i] = pid;
        }
    }

    // Close all pipes in parent
    for (int i = 0; i < NUM_COMMANDS - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes to terminate
    for (int i = 0; i < NUM_COMMANDS; i++) {
        waitpid(child_pids[i], NULL, 0);
    }

    return 0;
}
