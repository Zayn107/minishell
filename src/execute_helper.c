/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:23:58 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 09:53:31 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_while_process_is_sleeping(t_cmd *head)
{
	t_cmd	*cmd_node;

	cmd_node = head;
	while (cmd_node)
	{
		signal_all_children(head);
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

void	close_pipes(int pip1, int pip2)
{
	close(pip1);
	close(pip2);
}
