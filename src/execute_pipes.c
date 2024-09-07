/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:49:21 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/07 12:47:56 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_pipes(t_data *d, t_cmd *cmd_node)
{
	pipe(d->pip_in);
	if (cmd_node->prev && cmd_node->prev->cmd_arg[0] && cmd_node->prev->valid)
	{
		if (!cmd_node->prev->sleep)
			write_fd1_to_fd2(d->pip_out[READ], false, d->pip_in[WRITE], false);
		close(d->pip_out[READ]);
	}
	close(d->pip_in[WRITE]);
	d->is_pip_out = true;
	pipe(d->pip_out);
}

void	dup_close_fd_child(t_data *d, t_cmd *node)
{
	close(d->pip_out[READ]);
	if (node->fd_in != FD_NONE)
	{
		// printf("%s There is a fd_in, INPUT fd_in\n", node->cmd_arg[0]);
		dup2(node->fd_in, STDIN_FILENO);
	}
	else if (node->prev && !(node->prev->sleep))
	{
		// printf("%s There is a cmd before, and it is not sleeping, INPUT pipe_in[READ]\n", node->cmd_arg[0]);
		dup2(d->pip_in[READ], STDIN_FILENO);
	}
	if (node->fd_out != FD_NONE)
		dup2(node->fd_out, STDOUT_FILENO);
	else if (node->next)
		dup2(d->pip_out[WRITE], STDOUT_FILENO);
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
}

//write from fd_1 to fd_2, close fd_1 if close_1 true, same fd_2 and close_2
void	write_fd1_to_fd2(int fd_1, bool close_1, int fd_2, bool close_2)
{
	char	*buffer;

	while (true)
	{
		buffer = get_next_line(fd_1);
		if (NULL == buffer)
			break ;
		write(fd_2, buffer, ft_strlen(buffer));
		free(buffer);
	}
	if (close_1)
		close(fd_1);
	if (close_2)
		close(fd_2);
}
