/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:33:11 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 16:15:54 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_cmd_path(t_data *d, char *cmd)
{
	char	*env_path;
	char	**env_tab;

	if ((NULL != ft_strrchr(cmd, '/')))
		return (ft_strdup(cmd));
	env_path = env_value(d, "PATH");
	if (NULL == env_path)
		return (ft_strdup(cmd));
	env_tab = ft_split(env_path, ':');
	free(env_path);
	return (validate_env_path(env_tab, cmd));
}

char	*validate_env_path(char **env_tab, char *cmd)
{
	char	*slash;
	int		idx;
	char	*cmd_path;

	slash = ft_strdup("/");
	idx = 0;
	while (env_tab[idx])
	{
		cmd_path = join_free(&(env_tab[idx]), false, &slash, false);
		cmd_path = join_free(&(cmd_path), true, &(cmd), false);
		if ((0 == access(cmd_path, F_OK)))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		idx++;
	}
	free(slash);
	free_tab(env_tab);
	if (NULL == cmd_path)
		return (ft_strdup(cmd));
	return (cmd_path);
}
