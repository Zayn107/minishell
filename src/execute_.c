/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:46:18 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 21:25:11 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_data *d)
{
	t_cmd	*cmd_node;

	cmd_node = d->list_cmd;
	while (cmd_node)
	{
		if (NULL == cmd_node->cmd_arg[0] || !cmd_node->valid)
			cmd_node = skip_invalid_cmd(d, cmd_node, cmd_node->valid);
		else
		{
			create_pipes(d, cmd_node);
			if (cmd_node->process_child != shell_cmd)
				cmd_node = process_builtin(d, cmd_node);
			else
			{
				cmd_node->pid = fork();
				if (CHILD_PROCESS == cmd_node->pid)
					cmd_node->process_child(d, cmd_node);
				else
					cmd_node = process_parent(d, cmd_node);
			}
		}
		if (NULL == cmd_node && d->is_pip_out)
			close(d->pip_out[READ]);
	}
	wait_while_process_is_sleeping(d->list_cmd);
}

t_cmd	*skip_invalid_cmd(t_data *d, t_cmd *node, bool valid_cmd)
{
	if (!valid_cmd)
		d->exit_status = 1;
	return (node->next);
}

t_cmd	*process_parent(t_data *d, t_cmd *cmd_node)
{
	int	status;

	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	cmd_node->sleep = are_you_sleeping(cmd_node->pid);
	if (!cmd_node->sleep)
	{
		wait(&status);
		d->exit_status = WEXITSTATUS(status);
	}
	else
		close(d->pip_out[READ]);
	return (cmd_node->next);
}

void	shell_cmd(t_data *d, t_cmd *node)
{
	dup_close_fd_child(d, node);
	if ((execve(node->cmd_path, node->cmd_arg, d->env) == -1))
	{
		if (-1 == access(node->cmd_arg[0], F_OK))
			e_msg_and_exit(node->cmd_arg[0], ": command not found", 127);
		else if (EISDIR == errno)
			e_msg_and_exit(node->cmd_arg[0], ": Is a directory", 126);
		else if (node->cmd_arg[0][0] != '.' && node->cmd_arg[0][1] != '/')
			exit_if_directory_or_not_cmd(node->cmd_arg[0]);
		else
		{
			if (EISDIR == errno)
				e_msg_and_exit(node->cmd_arg[0], ": Is a directory", 126);
			else if (ENOEXEC == errno)
				e_msg_and_exit(node->cmd_arg[0], ": command not found", 127);
			else if (EACCES == errno)
				e_msg_and_exit(node->cmd_arg[0], ": Permission denied", 126);
		}
		perror("");
		exit(errno);
	}
}
