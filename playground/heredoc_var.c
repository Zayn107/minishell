

typedef struct s_doc_str
{
	char				*word;
	int					id;
	struct s_doc_str	*next;
}	t__doc_str;


#include "../include/minishell.h"

int	main(void)
{
	char	*input = "hello $USER $ $? $9invalid";




}

char	*evaluate_str_var(char *str, t_data *d, char *delimiter)
{
	int		idx;
	char	*start;
	char	*start_var;

	idx = 0;
	start = str;
	while (str[idx])
	{
		if ('$' == str[idx] && ' ' != str[idx +1])
		{
			start_var = str[idx++];
			if ('_' == str[idx] || ft_isalpha(str[idx]))
			idx++;
			while ('_' == idx_var[len] || ft_isalnum(idx_var[len]))
				idx++;
		}

		idx++;
	}
}