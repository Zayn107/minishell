/*Prompts the user for input which needs to be terminated with ENTER.
The code supposed to demonstrate the use of "rl_on_new_line()" by interrupting
the prompt with an message after which (thanks to the function) the curser
returns to the beginning of the line.
But this happens any way, even when commenting out the function.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// Function to simulate periodic status updates
void display_status() {
	// Print a status message
	printf("\nStatus: All systems operational");
	// Ensure the cursor is positioned correctly
	rl_on_new_line();
	rl_redisplay();
}

int main() {
	char *input;

	// Simulate periodic status updates in a separate thread or using signals
	if (fork() == 0) {
		while (1) {
			sleep(5);
			display_status();
		}
	}
	while ((input = readline("Prompt> ")) != NULL) {
		if (*input) {
			add_history(input);
			printf("You entered: %s\n", input);
		}
		free(input);
	}
	return 0;
}

/*
compile:
cc rl_on_new_line.c -o rl_on_new_line -lreadline -lhistory

run:
./rl_on_new_line
*/