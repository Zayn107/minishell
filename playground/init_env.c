#include "../include/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*ptr_start;
	char	*ptr_end;
	char	*str_1;
	char	*str_2;
	(void) argc;
	(void) argv;

	ptr_start = *env;
	ptr_end = ft_strchr(*env, '=');

	printf("%s\n", *env);
	// printf("%s\n", &env[0][ptr_end - ptr_start + 1]);
	// printf("%ld\n", ptr_end - ptr_start);

	str_1 = ft_substr(env[0], 0, ptr_end - ptr_start);
	str_2 = ft_substr(env[0], ptr_end - ptr_start + 1, ft_strlen(env[0]));
	printf("%s\n", str_1);
	printf("%s\n", str_2);

	free(str_1);
	free(str_2);
}

