/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_rest.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:22:38 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 15:44:32 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_echo(t_data *d, t_cmd *node)
{
	int		fd;
	int		arg;
	bool	new_line;

	arg = 1;
	new_line = true;
	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
		fd = d->pip_out[WRITE];
	else
		fd = STDOUT_FILENO;
	if (node->cmd_arg[1])
		if (((0 == ft_strncmp(node->cmd_arg[1], "-n", 2)) && arg++))
			new_line = false;
	write_echo(&(node->cmd_arg[arg]), fd, new_line);
	close(d->pip_out[WRITE]);
	d->exit_status = 0;
}

void	write_echo(char **argument, int fd, bool new_line)
{
	int	num;

	num = 0;
	while (argument[num])
	{
		write(fd, argument[num], ft_strlen(argument[num]));
		if (argument[num + 1])
			write(fd, " ", 1);
		num++;
	}
	if (new_line)
		write(fd, "\n", 1);
}
