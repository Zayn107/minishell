/*Print the current working directory before and after it is changed.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	const char *path = "/tmp";
	char *buffer;
	size_t size = 1024;

	// Allocate memory for the buffer
	buffer = (char *)malloc(size * sizeof(char));
	if (buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(EXIT_FAILURE);
	}
	// get the current working directory
	buffer = getcwd(buffer, size);
	printf("Before changing the working directory it is:\n %s\n\n", buffer);

	// Change the current working directory to /tmp
	if (chdir(path) == 0) {
		buffer = getcwd(buffer, size);
		printf("After changed working directory to:\n %s\n", buffer);

	} else {
		perror("chdir() error");
	}

	return 0;
}
/*
compile:
cc chdir.c -o chdir
*/

/*
run:
./chdir
*/