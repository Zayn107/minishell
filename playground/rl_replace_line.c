/*Demonstrate how the function "rl_replace_line()" works*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

// void replace_user_input(const char *current_text) {
void replace_user_input(void) {
	const char *new_string = "NEW STRING!";
	// Replace the "current line buffer" with "new_string"
	rl_replace_line(new_string, 0);
	/*"rl_line_buffer" is a global variable which contains the user input after
	calling readline()*/
	printf("your input is changed: %s\n", rl_line_buffer);
	/*Change what’s displayed on the screen to reflect the current contents of
	rl_line_buffer??? Appears to have no effect, even when changing the 
	order of the code.*/
	rl_redisplay();
}

int main() {
	char *input;

	while ((input = readline("Prompt> ")) != NULL) {
		if (*input) {
			printf("You entered: %s\n", input);
			// true if user entered "help"
			if (strcmp(input, "help") == 0) {
				replace_user_input();
			}
		}
		free(input);
	}
	return 0;
}

/*
compile:
cc rl_replace_line.c -o rl_replace_line -lreadline

run:
./rl_replace_line
*/

/*
void rl_replace_line(const char *text, int clear_undo);

-> *text:		A pointer to a null-terminated string containing the new line of
				text to replace the current line buffer.
-> clear_undo:	An integer that determines whether to clear the undo list.
				If non-zero, the undo list is cleared. If zero, the undo list is
				preserved.
*/
