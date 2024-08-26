/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_builtin_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:02:48 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/26 19:27:30 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//overwrite "shell_cmd" function with builtin fun pointer if cmd is builtin
void	assign_builtin(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while(current)
	{
		if ((0 == ft_strncmp(current->cmd_arg[0], "exit", 4)))
			current->process_child = builtin_exit;
		current = current->next;
	}
}

t_cmd	*process_builtin(t_data *d, t_cmd *node)
{
	node->process_child(d, node);
	return (node->next);
}

void	builtin_exit(t_data *d, t_cmd *node)
{
	int exit_code;

	exit_code = 0;
	organize_fds_according_list(d, node);
	if (node->cmd_arg[1])
	{

		if(is_digit(node->cmd_arg[1]))
			exit_code = ft_atoi(node->cmd_arg[1]);
		else
		{
			bash_msg3("bash: exit: ", node->cmd_arg[1],\
				": numeric argument required");
			exit_code = 255;
		}
	}
	free_all_except_env(d);
	free_tab(d->env);
	exit(exit_code);
}
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
