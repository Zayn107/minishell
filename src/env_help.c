/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:39:01 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 15:40:52 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	entry_match_var_name(char *entry, char *var_name)
{
	char	*ptr_equal;
	int		l_var;

	ptr_equal = ft_strchr(entry, '=');
	if (NULL != ptr_equal)
	{
		l_var = ptr_equal - entry;
		if (l_var == (int)ft_strlen(var_name))
			if ((0 == ft_strncmp(entry, var_name, l_var)))
				return (true);
	}
	return (false);
}

char	*get_env_tab_pos(char *identifier, char **env)
{
	int	row;

	row = 0;
	while (env[row])
	{
		if ((0 == ft_strncmp(env[row], identifier, ft_strlen(env[row]))))
			return (env[row]);
		row++;
	}
	return (NULL);
}
