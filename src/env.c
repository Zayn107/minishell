/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:12:43 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/28 16:21:17 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_env(t_data *d, char *arge[])
{
	int	len;
	// int	free_space;
	int	idx;
	
	len = 0;
	// free_space = 10;
	idx = 0;
	while (arge[len])
		len++;
	// d->env = (char **) malloc(sizeof(char *) * (len + free_space + 1));
	d->env = (char **) malloc(sizeof(char *) * (len + 1));

	// d->env = (char **) malloc(sizeof(char *) * (len + 1));
	// d->env[len + free_space] = NULL;
	d->env[len] = NULL;
	// d->env[len] = NULL;
	// while (arge[idx])
	// {
	// 	d->env[idx] = ft_strdup(arge[idx]);
	// 	// printf("create env: |%s|\n", d->env[idx]);
	// 	idx++;
	// }
	while (arge[idx])
	{
		d->env[idx] = ft_strdup(arge[idx]);
		// printf("create env: |%s|\n", d->env[idx]);
		idx++;
	}
	//was used to mark free space but design has changed
	// while (free_space--)
	// {
	// 	d->env[idx] = ft_strdup("!FREE!");
	// 	// printf("create env: |%s|\n", d->env[idx]);
	// 	idx++;
	// }
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
			// printf("inside env_vale: %s\n", &(d->env[idx][len_var + 1]));
			return ft_strdup(&(d->env[idx][len_var + 1]));
			// return &(d->env[idx][len_var + 1]);
		}
		idx++;
	}
	return NULL;
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
