#include "../include/minishell.h"

int	main(void)
{
	char	*sub;
	// char	*trim;

	sub = ft_substr("abc'quote'123", 4, 5);
	printf("sub  |%s|\n", sub);
	// if (sub)
	// 	printf("sub true\n");
	// trim = ft_strtrim(sub, " ");
	// printf("trim |%s|\n", trim);
	// if (trim[0] == '\0')
	// 	printf("trim empty\n");
	free(sub);
}
