/*Promt the user for input which needs to be terminated with ENTER. The user can
cycle through the command history with the UP and DOWN arrow keys unless the
history has been cleared with the "clear" command. To exit press CTRL + C.*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void clear_command_history() {
	rl_clear_history();
	printf("Command history cleared.\n");
}

int main() {
	char *input;

	while ((input = readline("Prompt> ")) != NULL) {
		if (*input) {
			// Add the input line to the history
			add_history(input);
			// Process the input
			printf("You entered: %s\n", input);
			// Example command to clear the history
			if (strcmp(input, "clear") == 0) {
				clear_command_history();
			}
		}
		// Free the allocated memory for the input
		free(input);

	}
	return 0;
}

/*
compile:
cc rl_clear_history.c -o rl_clear_history -lreadline -lhistory

run:
./rl_clear_history
*/