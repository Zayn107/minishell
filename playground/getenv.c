/*read shell environment variables, in this example "Path"*/
#include <stdio.h>
#include <stdlib.h>

int main() {
	char *path;

	// Retrieve the value of the PATH environment variable
	path = getenv("PATH");
	if (path != NULL) {
		printf("PATH: %s\n", path);
	} else {
		printf("PATH environment variable not found.\n");
	}

	return 0;
}
/*compile:
cc getenv.c -o getenv

run:
./getenv
*/
