/*list all files from an directory*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
	const char *path = "../playground";
	DIR *dir;
	struct dirent *entry;

	// Open the directory
	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		return EXIT_FAILURE;
	}

	// Read the directory entries
	while ((entry = readdir(dir)) != NULL) {
		printf("Found: %s\n", entry->d_name);
	}

	// Close the directory
	if (closedir(dir) == -1) {
		perror("closedir");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*compile:
cc dir.c -o dir

run:
./dir
*/