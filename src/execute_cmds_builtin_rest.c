/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_builtin_rest.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:22:38 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 16:14:52 by zkepes           ###   ########.fr       */
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
		}
		else
			bash_msg(node->cmd_arg[0], ": missing argument");
	}
	else if (NULL != node->cmd_arg[2])
		bash_msg(node->cmd_arg[0], ": too many arguments");
	else if (chdir(node->cmd_arg[1]))
	{
		if (EACCES == errno)
			bash_msg3("bash: cd: ", node->cmd_arg[1], ": Permission denied");
		else if (ENOENT == errno)
			bash_msg3(\
			"bash: cd: ", node->cmd_arg[1], ": No such file or directory");
	}
}

void	builtin_pwd(t_data *d, t_cmd *node)
{
	int		fd;
	char	*buffer;
	bool	close_pipe_out;

	close_pipe_out = true;
	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
	{
		fd = d->pip_out[WRITE];
		close_pipe_out = false;
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
}

void	builtin_exit(t_data *d, t_cmd *node)
{
	int	exit_code;

	exit_code = 0;
	if (node->cmd_arg[1])
	{
		if (is_digit(node->cmd_arg[1]))
			exit_code = ft_atoi(node->cmd_arg[1]);
		else
		{
			bash_msg3("bash: exit: ", node->cmd_arg[1], \
				": numeric argument required");
			exit_code = 255;
		}
	}
	free_all_except_env(d);
	free_tab(d->env);
	exit(exit_code);
}

void	builtin_echo(t_data *d, t_cmd *node)
{
	int		fd;
	int		arg;
	bool	close_pipe_out;
	bool	new_line;

	arg = 1;
	close_pipe_out = true;
	new_line = true;
	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
	{
		fd = d->pip_out[WRITE];
		close_pipe_out = false;
	}
	else
		fd = STDOUT_FILENO;
	if (node->cmd_arg[1])
		if (((0 == ft_strncmp(node->cmd_arg[1], "-n", 2)) && arg++))
			new_line = false;
	write_echo(&(node->cmd_arg[arg]), fd, new_line);
	close(d->pip_out[WRITE]);
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
		else if (new_line)
			write(fd, "\n", 1);
		num++;
	}
}
