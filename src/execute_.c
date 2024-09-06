/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:46:18 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/06 10:08:53 by zkepes           ###   ########.fr       */
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
		if (NULL == cmd_node)
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
		//printf("cmd: %s, stat: %d exit stat: %d\n", cmd_node->cmd_arg[0], WEXITSTATUS(status), d->exit_status);
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
		{
			e_msg1(node->cmd_arg[0], ": command not found");
			exit(127);
		}
		else
		{
			if (EISDIR == errno)
			{
				e_msg1(node->cmd_arg[0], ": Is a directory");
				exit(126);
			}
			else if (ENOEXEC == errno)
			{
				e_msg1(node->cmd_arg[0], ": command not found");
				exit(127);
			}
			else if (EACCES == errno)
			{
				e_msg1(node->cmd_arg[0], ": Permission denied");
				exit(126);
			}
		}
		perror("");
		exit(errno);
	}
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
			// printf("%s is still sleeping, pid: %d\n", cmd_node->cmd_arg[0], cmd_node->pid);
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
