/*Create a file and delete a file. Try and see what happens when you comment the
file creating out and try to delete it after.*/

#include <stdio.h>
#include <unistd.h>

int main() {
	const char *path = "filename.txt";
	FILE *fptr;

	// Create a file
	fptr = fopen(path, "w");
	// Close the file
	fclose(fptr); 
	
	// Delete the file
	if (unlink(path) == 0) {
		printf("Successfully deleted the file: %s\n", path);
	} else {
		perror("unlink");
	}

	return 0;
}
/*
compile:
cc unlink.c -o unlink

run:
./unlink
*/