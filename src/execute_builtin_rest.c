/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_rest.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:22:38 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 12:13:11 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_cd(t_data *d, t_cmd *node)
{
	char	*path_home;

	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	if (NULL == node->cmd_arg[1])
	{
		path_home = env_value(d, "HOME");
		if (path_home)
		{
			chdir(path_home);
			free(path_home);
			d->exit_status = 0;
		}
		else
			e_fd_msg1(d, node->cmd_arg[0], ": missing argument");
	}
	else if (NULL != node->cmd_arg[2])
		e_fd_msg1(d, node->cmd_arg[0], ": too many arguments");
	else if (chdir(node->cmd_arg[1]))
	{
		if (EACCES == errno)
			e_msg3(d, "bash: cd: ", node->cmd_arg[1], ": Permission denied");
		else if (ENOENT == errno)
			e_msg3(d, \
			"bash: cd: ", node->cmd_arg[1], ": No such file or directory");
	}
}

void	builtin_pwd(t_data *d, t_cmd *node)
{
	int		fd;
	char	*buffer;
	// bool	close_pipe_out;

	// close_pipe_out = true;
	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
	{
		fd = d->pip_out[WRITE];
		// close_pipe_out = false;
	}
	else
		fd = STDOUT_FILENO;
	buffer = getcwd(NULL, 0);
	if (NULL != buffer)
	{
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	else
		perror("getcwd() error");
	close(d->pip_out[WRITE]);
	d->exit_status = 0;
}

void	builtin_echo(t_data *d, t_cmd *node)
{
	int		fd;
	int		arg;
	// bool	close_pipe_out;
	bool	new_line;

	arg = 1;
	// close_pipe_out = true;
	new_line = true;
	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
	{
		fd = d->pip_out[WRITE];
		// close_pipe_out = false;
	}
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
