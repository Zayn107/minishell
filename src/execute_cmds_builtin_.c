/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_builtin_.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:02:48 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/03 13:06:46 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//overwrite "shell_cmd" function with builtin fun pointer if cmd is builtin
void	assign_builtin(t_cmd *head)
{
	t_cmd		*current;
	const int	cmd = 0;

	current = head;
	while (current)
	{
		if (current->cmd_arg[cmd])
		{
			if ((0 == ft_strncmp(current->cmd_arg[cmd], "exit", 4)))
				current->process_child = builtin_exit;
			else if ((0 == ft_strncmp(current->cmd_arg[cmd], "env", 3)))
				current->process_child = builtin_env;
			else if ((0 == ft_strncmp(current->cmd_arg[cmd], "export", 6)))
				current->process_child = builtin_export;
			else if ((0 == ft_strncmp(current->cmd_arg[cmd], "unset", 5)))
				current->process_child = builtin_unset;
			else if ((0 == ft_strncmp(current->cmd_arg[cmd], "cd", 2)))
				current->process_child = builtin_cd;
			else if ((0 == ft_strncmp(current->cmd_arg[cmd], "pwd", 3)))
				current->process_child = builtin_pwd;
			else if ((0 == ft_strncmp(current->cmd_arg[cmd], "echo", 4)))
				current->process_child = builtin_echo;
		}
		current = current->next;
	}
}

t_cmd	*process_builtin(t_data *d, t_cmd *node)
{
	node->process_child(d, node);
	return (node->next);
}

bool	is_single_cmd(t_cmd *node)
{
	if (NULL == node->prev && NULL == node->next)
		return (true);
	else
		return (false);
}