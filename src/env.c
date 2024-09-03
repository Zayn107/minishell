/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:12:43 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/03 09:48:29 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_env(t_data *d, char *arge[])
{
	int	len;
	int	idx;

	len = 0;
	idx = 0;
	d->exit_status = 0;
	while (arge[len])
		len++;
	d->env = (char **) malloc(sizeof(char *) * (len + 1));
	d->env[len] = NULL;
	while (arge[idx])
	{
		d->env[idx] = ft_strdup(arge[idx]);
		idx++;
	}
}

/*returns a pointer to the value of the "env variable name", if not exist
return NULL which can cause problems with printf*/
char	*env_value(t_data *d, char *var_name)
{
	int		idx;
	int		len_var;

	idx = 0;
	len_var = ft_strlen(var_name);
	while (d->env[idx])
	{
		if (!ft_strncmp(d->env[idx], var_name, len_var)
			&& d->env[idx][len_var] == '=')
		{
			return (ft_strdup(&(d->env[idx][len_var + 1])));
		}
		idx++;
	}
	return (NULL);
}

//malloc var and add to d->env
void	add_to_env(t_data *d, char *var)
{
	int		len_env;
	int		idx;
	char	**new_env;

	len_env = 0;
	while (d->env[len_env])
		len_env++;
	new_env = (char **) malloc(sizeof(char *) * (len_env + 2));
	idx = 0;
	while (d->env[idx])
	{
		new_env[idx] = d->env[idx];
		idx++;
	}
	new_env[idx] = ft_strdup(var);
	new_env[idx + 1] = NULL;
	free(d->env);
	d->env = new_env;
}

char	**remove_entry_from_env(char **env, char *entry)
{
	int		len;
	int		idx;
	int		idx_new;
	char	**new_env_tab;

	len = 0;
	idx = 0;
	idx_new = 0;
	while (env[len])
		len++;
	new_env_tab = (char **) malloc(sizeof(char *) * len);
	while (env[idx])
	{
		if ((0 == ft_strncmp(env[idx], entry, ft_strlen(entry))) && idx++)
			continue ;
		new_env_tab[idx_new] = env[idx];
		idx++;
		idx_new++;
	}
	new_env_tab[len - 1] = NULL;
	free(env);
	free(entry);
	return (new_env_tab);
}

char	*get_env_tab_pos(char *identifier, char **env)
{
	int	row;

	row = 0;
	while (env[row])
	{
		if ((0 == ft_strncmp(env[row], identifier, ft_strlen(identifier))))
			return (env[row]);
		row++;
	}
	return (NULL);
}
