/*Keeps prompting the user for input which needs to be terminated with ËNTER and
prints it to the screen. Exit with CTRL + C.*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main() {
	char *input;

	while ((input = readline("Prompt> ")) != NULL) {
		if (*input) {
			printf("You entered: %s\n", input);
		}
		free(input);
	}
	return 0;
}

/*
compile:
cc readline.c -o readline -lreadline

run:
./readline
*/
