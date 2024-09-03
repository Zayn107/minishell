#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int	ft_atoi(const char *str)
{
	int		num;
	int		idx;
	bool	neg;

	num = 0;
	idx = 0;
	neg = false;
	while (((str[idx]) >= 9 && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			neg = true;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
		num = (num * 10) + (str[idx++] - '0');
	if (neg)
		return (num * -1);
	return (num);
}

int	atoi_real_n(const char *str, bool *is_digit)
{
	int		num;
	int		idx;
	bool	neg;

	num = 0;
	idx = 0;
	neg = false;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			neg = true;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
		num = (num * 10) + (str[idx++] - '0');
	if (idx != (int)strlen(str))
		*is_digit = false;
	else
		*is_digit = true;
	if (neg)
		return (num * -1);
	return (num);
}



int		main(int argc, char *argv[])
{
	(void) argc;
	bool	is_digit;
	int		num;

	if (argv[1])
	{
		num = atoi_real_n(argv[1], &is_digit);
		printf("num is: %d bool is: %d\n", num, (int)is_digit);
	}
}