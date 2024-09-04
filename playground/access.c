#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void)
{
	if (-1 == access("sample.txt", W_OK))
		printf("permission denied\n");
}