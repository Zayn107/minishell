/*Prints out some information about a file, there is more information stored in
the structure.*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	struct stat fileStat;
	// make sure the path still points to a valid file
	const char *path = "../doc/minishell.pdf";

	if (stat(path, &fileStat) < 0) {
		perror("stat");
		return 1;
	}

	printf("Information for %s\n", path);
	printf("---------------------------\n");
	printf("File Size: \t\t%ld bytes\n", fileStat.st_size);
	printf("Number of Links: \t%ld\n", fileStat.st_nlink);
	printf("File inode: \t\t%ld\n", fileStat.st_ino);
	printf("File Permissions: \t");
	printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n");
	return 0;
}
/*
compile:
cc stat.c -o stat

run:
./stat
*/

