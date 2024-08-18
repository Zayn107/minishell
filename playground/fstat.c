/*Prints out some information about a file, there is more information stored in
the structure.*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	struct stat fileStat;
	int fd;

	// Open the file
	fd = open("../doc/minishell.pdf", O_RDONLY);
	if (fd < 0) {
		perror("open");
		return 1;
	}
	// Get file status
	if (fstat(fd, &fileStat) < 0) {
		perror("fstat");
		close(fd);
		return 1;
	}

	printf("Information for '../doc/minishell.pdf'");
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
	// Close the file
	close(fd);
	return 0;
}
/*
compile:
cc fstat.c -o fstat

run:
./fstat
*/

