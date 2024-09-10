/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:16:31 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 15:35:44 by zkepes           ###   ########.fr       */
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
			if (!found_replace_var_env(node->cmd_arg[arg], identifier, d))
				add_var_to_env(d, node->cmd_arg[arg]);
		}
		free(identifier);
		arg++;
	}
}

bool	found_replace_var_env(char *var, char *identifier, t_data *d)
{
	int	row;

	row = 0;
	while (d->env[row])
	{
		if (entry_match_var_name(d->env[row], identifier))
		{
			free(d->env[row]);
			d->env[row] = ft_strdup(var);
			return (true);
		}
		row++;
	}
	return (false);
}

//exit status is 0 even if it is not removing var, does nothing in a pipe
void	builtin_unset(t_data *d, t_cmd *node)
{
	int		arg;
	int		row;

	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	d->exit_status = 0;
	arg = 1;
	if (!is_single_cmd(node))
		return ;
	while (node->cmd_arg[arg])
	{
		row = 0;
		while (d->env[row])
		{
			if (entry_match_var_name(d->env[row], node->cmd_arg[arg]))
				d->env = remove_entry_env(d->env, node->cmd_arg[arg]);
			else
				row++;
		}
		arg++;
	}
}
