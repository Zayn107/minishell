/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_fun_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:58:55 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/27 13:55:15 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shell_cmd(t_data *d, t_cmd *node)
{
	dup_close_fd_child(d, node);
	if ((execve(node->cmd_path, node->cmd_arg, NULL) == -1))
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		bash_msg2(node->cmd_arg[0], ": command not found");
	}
	exit(127);
}

// void	assign_builtin(t_cmd *head)
// {
// 	t_cmd	*current;

// 	current = head;
// 	while (current)
// 	{
// 		// if (current->cmd_arg[0] == "pwd")
// 		if ((0 == ft_strncmp(current->cmd_arg[0], "echo", 4)))
// 			current->process_child = builtin_echo;
// 		current = current->next;
// 	}
// }
