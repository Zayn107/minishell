/*Prompts the user for input which needs to be terminated with ENTER which is
then printed to the screen. With the UP and DOWN ARROW key, the usr can cycle
through previous entry's (commands). Press CTRL + C to exit.*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
	char *input;

	while ((input = readline("Prompt> ")) != NULL) {
		if (*input) {
			// Add the input line to the history
			add_history(input);
			// Process the input (for example, by printing it)
			printf("You entered: %s\n", input);
		}
		// Free the allocated memory for the input
		free(input);
	}

	return 0;
}

/*
compile:
cc add_history.c -o add_history -lreadline -lhistory

run:
./add_history
*/