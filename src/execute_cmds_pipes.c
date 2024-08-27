/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:49:21 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/27 16:17:29 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ORIGINAL
// void	create_pipes(t_data *d, t_cmd *cmd_node)
// {
// 	pipe(d->pip_in);
// 	if (cmd_node->prev && !cmd_node->sleep) //if there was a process before
// 	{
// 		write_fd1_to_fd2(d->pip_out[READ], d->pip_in[WRITE], false);
// 		close(d->pip_out[READ]);
// 	}
// 	pipe(d->pip_out);
// }


void	create_pipes(t_data *d, t_cmd *cmd_node)
{
	pipe(d->pip_in);
	if (cmd_node->prev)
	{
		if(!cmd_node->prev->sleep)
			write_fd1_to_fd2(d->pip_out[READ], false, d->pip_in[WRITE], false);
		close(d->pip_out[READ]);
	}
	close(d->pip_in[WRITE]);
	pipe(d->pip_out);
}

void	dup_close_fd_child(t_data *d, t_cmd *node)
{
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
	// if (NULL != node->file_out)
	if (node->fd_out != FD_NONE)
	{
		// if (node->is_append)
		// 	fd = open(node->file_out, O_APPEND, 0664);
		// else
		// 	fd = open(node->file_out, O_WRONLY);
		// printf("fd: %d\n", fd);
		// // printf("fd_out, fd:%d cmd: %s \n", node->fd_out, node->cmd_arg[0]);
		// if (node->is_append)
		// 	printf("is append: true\n");
		// else
		// 	printf("is append: false\n");
		dup2(node->fd_out, STDOUT_FILENO);
	}
	else if (node->next)
	{
		// printf("pipe out, cmd: %s \n", node->cmd_arg[0]);
		dup2(d->pip_out[WRITE], STDOUT_FILENO);
	}
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
}

// void	dup_close_fd_child(t_data *d, t_cmd *node)
// {
// 	close(d->pip_out[READ]);
// 	if (node->fd_in != FD_NONE)
// 	{
// 		printf("fd_in is true, fd:%d cmd: %s \n", node->fd_in, node->cmd_arg[0]);
// 		dup2(node->fd_in, STDIN_FILENO);
// 	}
// 	else if (node->prev && !(node->prev->sleep))
// 	{
// 		printf("pipe in read, cmd: %s \n", node->cmd_arg[0]);
// 		dup2(d->pip_in[READ], STDIN_FILENO);
// 	}
// 	if (node->fd_out != FD_NONE)
// 	{
// 		printf("fd_out, fd:%d cmd: %s \n", node->fd_out, node->cmd_arg[0]);
// 		if (node->is_append)
// 			printf("is append: true\n");
// 		else
// 			printf("is append: false\n");
// 		dup2(node->fd_out, STDOUT_FILENO);
// 	}
// 	else if (node->next)
// 	{
// 		printf("pipe out, cmd: %s \n", node->cmd_arg[0]);
// 		dup2(d->pip_out[WRITE], STDOUT_FILENO);
// 	}
// 	close(d->pip_in[READ]);
// 	close(d->pip_out[WRITE]);
// }