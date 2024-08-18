/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:00:07 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/16 14:14:04 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*cut the characters from "cut_str from "str" beginning and end*/
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