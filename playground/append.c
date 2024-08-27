#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


int	main(int argc, char *argv[])
{
	int	fd;

	(void) argc;

	fd = open("file1", O_APPEND | O_RDWR);
	printf("argv[1]: %s fd: %d\n", argv[1], fd);
	write(fd, argv[1], strlen(argv[1]));
}