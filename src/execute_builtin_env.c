/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:16:31 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 13:51:10 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_env(t_data *d, t_cmd *node)
{
	int		row;
	int		fd;

	row = 0;
	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
		fd = d->pip_out[WRITE];
	else
		fd = STDOUT_FILENO;
	while (d->env[row])
	{
		write(fd, d->env[row], ft_strlen(d->env[row]));
		write(fd, "\n", 1);
		row++;
	}
	close(d->pip_out[WRITE]);
	d->exit_status = 0;
}

void	builtin_export(t_data *d, t_cmd *node)
{
	int		arg;
	char	*identifier;
	char	*pos_env_tab;

	d->exit_status = 0;
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	arg = 1;
	while (node->cmd_arg[arg])
	{
		identifier = get_identifier_name(node->cmd_arg[arg]);
		if (identifier_is_invalid(node->cmd_arg[arg]))
			e_msg3(d, \
			"bash: export: `", node->cmd_arg[arg], "': not a valid identifier");
		else if (identifier && is_single_cmd(node))
		{
			pos_env_tab = get_env_tab_pos(identifier, d->env);
			if (NULL != pos_env_tab)
				replace_s1_with_s2(&pos_env_tab, node->cmd_arg[arg]);
			else
				add_to_env(d, node->cmd_arg[arg]);
		}
		free(identifier);
		arg++;
	}
}

//exit status is 0 even if it is not removing var, does nothing in a pipe
void	builtin_unset(t_data *d, t_cmd *node)
{
	int		arg;
	char	*pos_env_tab;

	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	d->exit_status = 0;
	if (!is_single_cmd(node))
		return;
	arg = 1;
	while (node->cmd_arg[arg])
	{
		pos_env_tab = get_env_tab_pos(node->cmd_arg[arg], d->env);
		if (pos_env_tab)
			d->env = remove_entry_from_env(d->env, pos_env_tab);
		arg++;
	}
}

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
