/*Prints the current working directory to the screen.*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char *buffer;
	size_t size = 1024;

	// Allocate memory for the buffer
	buffer = (char *)malloc(size * sizeof(char));
	if (buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(EXIT_FAILURE);
	}
	// Get the current working directory
	if (getcwd(buffer, size) != NULL) {
		printf("Current working directory: %s\n", buffer);
	} else {
		perror("getcwd() error");
	}
	// Free the allocated buffer
	free(buffer);
	return 0;
}

/*
compile:
cc getcwd.c -o getcwd
*/

/*
run:
./getcwd
*/