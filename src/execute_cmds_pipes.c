/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:49:21 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/24 20:21:56 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_pipes(t_data *d, t_cmd *cmd_node)
{
	pipe(d->pip_in);
	if (cmd_node->prev && !cmd_node->sleep)
		copy_pipe_content(d->pip_out[READ], d->pip_in[WRITE], false);
	close(d->pip_out[READ]);
	pipe(d->pip_out);
}

void	organize_fds_according_list(t_data *d, t_cmd *node)
{
	close(d->pip_in[WRITE]);
	close(d->pip_out[READ]);
	if (node->fd_in != FD_NONE)
	{
		// printf("fd_in is true, fd:%d cmd: %s \n", node->fd_in, node->cmd_arg[0]);
		dup2(node->fd_in, STDIN_FILENO);
	}
	else if (node->prev && !(node->prev->sleep))
	{
		// printf("pipe in read, cmd: %s \n", node->cmd_arg[0]);
		dup2(d->pip_in[READ], STDIN_FILENO);
	}
	if (node->fd_out != FD_NONE)
	{
		// printf("fd_out, fd:%d cmd: %s \n", node->fd_out, node->cmd_arg[0]);
		dup2(node->fd_out, STDOUT_FILENO);
	}
	else
	{
		// printf("pipe out, cmd: %s \n", node->cmd_arg[0]);
		dup2(d->pip_out[WRITE], STDOUT_FILENO);
	}
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
}
