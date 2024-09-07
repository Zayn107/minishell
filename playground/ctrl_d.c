#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(void)
{
	char	buffer[1];
	int		result;

	while (true)
	{
		result = read(0, buffer, 1);
		printf("%s result: %d\n", buffer, result);
		if (result == 0)
			printf("the end\n");
	}
}
