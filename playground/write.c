#include <unistd.h>

int	main(void)
{
	write(2, "\033[1;41m", 7);
	write(2, "hello\n", 6);
	write(2, "\033[0m", 4);
	write(2, "world", 5);
}