/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:24:54 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/28 15:36:26 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*cut "str" from the index to end, return new Malloc, free "str"*/
char	*cut_str(char *str, int start)
{
	char	*tmp;

	tmp = ft_strdup(&(str[start]));
	free(str);
	return (tmp);
}

/*cut the characters from "cut_str" from "str" beginning and end*/
void	trim_str(char **str, char *cut_str)
{
	char	*trimmed;

	trimmed = ft_strtrim(*str, cut_str);
	free(*str);
	*str = trimmed;
}

/*joins str1 and str2 and returned as a malloc, if bool true str is freed*/
char	*join_free(char **str1, bool free_s1, char **str2, bool free_s2)
{
	char	*join;

	join = ft_strjoin(*str1, *str2);
	if (free_s1)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (free_s2)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (join);
}

/*returns the length of an matching quoted string, if no match then 0*/
int	matching_quote_len(const char *str)
{
	int		idx;
	char	quote;

	idx= 1;
	if ('"' == *str || '\'' == *str)
	{
		quote = str[0];
		while (str[idx])
		{
			if (str[idx] == quote)
				return ++idx;
			idx++;
		}
	}
	return 0;
}

//true if the string contains only digits
bool	is_digit(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			return (false);
		idx++;
	}
	return (true);
}

void	replace_s1_with_s2(char **str1, char *str2)
{
	free(*str1);
	*str1 = ft_strdup(str2);
}