/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_builtin_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:02:48 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/24 18:05:11 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	builtin_echo(t_data *d, t_cmd *node)
// {
// 	int	idx;

// 	(void) d;
// 	idx = 1;
// 	if (NULL == node->file_out && NULL == node->next)
// 		node->fd_out = STDOUT_FILENO;
// 	while (node->cmd_arg[idx])
// 	{
// 		if (idx > 1)
// 			write(node->fd_out, " ", 1);
// 		write(node->fd_out, node->cmd_arg[idx], ft_strlen(node->cmd_arg[idx]));
// 		idx++;
// 	}
// 	write(node->fd_out, "\n", 1);
// }
