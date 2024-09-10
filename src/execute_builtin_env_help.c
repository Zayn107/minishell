/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_env_help.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:25:08 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 09:26:25 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//valid if 1st= alphabetic or underscore, 2nd= can also be numeric
bool	identifier_is_invalid(const char *str)
{
	int	idx;

	idx = 0;
	if (ft_isalpha(str[idx]) || '_' == str[idx])
		idx++;
	else
		return (true);
	while (str[idx] && '=' != str[idx])
	{
		if (ft_isalpha(str[idx]) || '_' == str[idx] || ft_isdigit(str[idx]))
			idx++;
		else
			return (true);
	}
	return (false);
}

//return NULL if no '=', else MALLOCED str with identifier
char	*get_identifier_name(char *str)
{
	char	*ptr_equal;

	ptr_equal = ft_strchr(str, '=');
	if (NULL == ptr_equal)
		return (NULL);
	return (ft_substr(str, 0, ptr_equal - &(str[0])));
}
