/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:46:18 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 15:58:53 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_cmds(t_data *d)
{
	t_cmd	*cmd_node;

	cmd_node = d->list_cmd;
	while (cmd_node)
	{
		if (NULL == cmd_node->cmd_arg[0])
			cmd_node = cmd_node->next;
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
		if (NULL == cmd_node)
			close(d->pip_out[READ]);
	}
	wait_while_process_is_sleeping(d->list_cmd);
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
		dup2(STDERR_FILENO, STDOUT_FILENO);
		bash_msg2(node->cmd_arg[0], ": command not found");
	}
	exit(127);
}

void	wait_while_process_is_sleeping(t_cmd *head)
{
	t_cmd	*cmd_node;

	cmd_node = head;
	while (cmd_node)
	{
		if (cmd_node->sleep)
		{
			cmd_node->sleep = are_you_sleeping(cmd_node->pid);
			cmd_node = head;
			continue ;
		}
		cmd_node = cmd_node->next;
	}
}

bool	are_you_sleeping(pid_t pid)
{
	char	*path;
	char	*str_pid;
	char	*buffer;
	int		fd;
	bool	is_sleeping;

	is_sleeping = false;
	str_pid = ft_itoa(pid);
	buffer = ft_strdup("/proc/");
	path = join_free(&buffer, true, &str_pid, true);
	buffer = ft_strdup("/status");
	path = join_free(&path, true, &buffer, true);
	fd = open(path, O_RDONLY);
	free(path);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (ft_strnstr(buffer, "S (sleeping)", ft_strlen(buffer)))
			is_sleeping = true;
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (is_sleeping);
}
