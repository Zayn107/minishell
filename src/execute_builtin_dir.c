/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:43:11 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 15:52:39 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_cd(t_data *d, t_cmd *node)
{
	char	*path_new_dir;

	close_pipes(d->pip_in[READ], d->pip_out[WRITE]);
	d->exit_status = EXIT_SUCCESS;
	if (NULL == node->cmd_arg[1])
		if_env_cd_home(d, node);
	else if (NULL != node->cmd_arg[2])
		e_fd_msg1(d, node->cmd_arg[0], ": too many arguments");
	else
	{
		if (chdir(node->cmd_arg[1]))
			handle_chdir_errors(d, node->cmd_arg[1], errno);
		else
		{
			path_new_dir = getcwd(NULL, 0);
			if (path_new_dir)
				update_pwd_and_oldpwd(d, path_new_dir);
			free(path_new_dir);
		}
	}
}

void	handle_chdir_errors(t_data *d, char *path, int e_code)
{
	if (EACCES == e_code)
		e_msg3(d, "bash: cd: ", path, ": Permission denied");
	else if (ENOENT == e_code)
		e_msg3(d, \
				"bash: cd: ", path, ": No such file or directory");
}

void	update_pwd_and_oldpwd(t_data *d, char *path)
{
	char	*e_entry;
	char	*e_value;

	e_entry = NULL;
	e_value = NULL;
	if (has_var_name(d->env, "PWD"))
	{
		e_value = env_value(d, "PWD");
		e_entry = ft_strjoin("OLDPWD=", e_value);
		if (!found_replace_var_env(e_entry, "OLDPWD", d))
			add_var_to_env(d, e_entry);
		free(e_value);
		free(e_entry);
	}
	e_entry = ft_strjoin("PWD=", path);
	if (!found_replace_var_env(e_entry, "PWD", d))
		add_var_to_env(d, e_entry);
	free(e_entry);
}

void	if_env_cd_home(t_data *d, t_cmd *node)
{
	char	*path_home;

	path_home = env_value(d, "HOME");
	if (path_home)
	{
		update_pwd_and_oldpwd(d, path_home);
		chdir(path_home);
		free(path_home);
		d->exit_status = EXIT_SUCCESS;
	}
	else
		e_fd_msg1(d, node->cmd_arg[0], ": missing argument");
}

void	builtin_pwd(t_data *d, t_cmd *node)
{
	int		fd;
	char	*buffer;

	close(d->pip_in[READ]);
	if (node->fd_out != FD_NONE)
		fd = node->fd_out;
	else if (node->next)
		fd = d->pip_out[WRITE];
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
