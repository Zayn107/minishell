#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <fcntl.h>
// #include <stxetx.h>


int	main(void)
{
	char	buffer[2];
	int		result;
	signal(SIGINT, SIG_IGN);
	// int		count = 20;
	printf("this is input test\n");
	while (true)
	{
		// printf("hello\n");
		result = read(0, buffer, 1);
		buffer[1] = '\0';
		if (3 == (buffer[0] + 48))
			printf("ctrl + c\n");
		// if ('^' == buffer[0] && 'C' == buffer[1])

		// write(1, buffer, 2);
	}

	(void) result;
}
