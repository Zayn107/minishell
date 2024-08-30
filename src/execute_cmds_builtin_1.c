/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_builtin_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:02:48 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/30 18:46:57 by zkepes           ###   ########.fr       */
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
		else if ((0 == ft_strncmp(current->cmd_arg[0], "env", 3)))
			current->process_child = builtin_env;
		else if ((0 == ft_strncmp(current->cmd_arg[0], "export", 6)))
			current->process_child = builtin_export;
		else if ((0 == ft_strncmp(current->cmd_arg[0], "unset", 5)))
			current->process_child = builtin_unset;
		else if ((0 == ft_strncmp(current->cmd_arg[0], "cd", 2)))
			current->process_child = builtin_cd;
		else if ((0 == ft_strncmp(current->cmd_arg[0], "pwd", 3)))
			current->process_child = builtin_pwd;
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
	// close(d->pip_in[READ]);
	// close(d->pip_out[WRITE]);
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

void	builtin_env(t_data *d, t_cmd *node)
{
	int		idx;
	int		fd;
	bool	close_pipe_out;

	idx = 0;
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
	while (d->env[idx])
	{
		write(fd, d->env[idx], ft_strlen(d->env[idx]));
		write(fd, "\n", 1);
		idx++;
	}
	close(d->pip_out[WRITE]);
}

void	builtin_export(t_data *d, t_cmd *node)
{
	int		arg;
	char	*identifier;
	char	*pos_env_tab;
	
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	arg = 1;
	while (node->cmd_arg[arg])
	{
		identifier = get_identifier_name(node->cmd_arg[arg]);
		if (identifier_is_invalid(node->cmd_arg[arg]))
			bash_msg3(\
			"bash: export: `", node->cmd_arg[arg], "': not a valid identifier");
		else if (identifier)
		{
			if ((NULL != (pos_env_tab = get_env_tab_pos(identifier, d->env))))
				replace_s1_with_s2(&pos_env_tab, node->cmd_arg[arg]);
			else
				add_to_env(d, node->cmd_arg[arg]);
		}
		free(identifier);
		arg++;
	}
}

// char	*get_env_tab_pos(char *identifier, t_data *d)
char	*get_env_tab_pos(char *identifier, char **env)
{
	int	row;

	row = 0;
	while (env[row])
	{
		if ((0 == ft_strncmp(env[row], identifier, ft_strlen(identifier))))
			return (env[row]);
		row++;
	}
	return (NULL);
}

//return NULL if no '=', else MALLOCED str with identifier
char	*get_identifier_name(char *str)
{
	char	*ptr_equal;
	// char	*ptr_last;

	if ((NULL == (ptr_equal = ft_strchr(str, '='))))
		return (NULL);
	// ptr_last = &(str[ft_strlen(str) - 1]);
	return (ft_substr(str, 0, ptr_equal - &(str[0])));
}

//valid if 1st= alphabetic or underscore, 2nd= can also be numeric
bool	identifier_is_invalid(const char *str)
{
	int	idx;

	idx = 0;
	if (ft_isalpha(str[idx]) || '_' == str[idx])
		idx++;
	else
		return (true);
	while (str[idx] && '=' != str[idx])
	{
		if (ft_isalpha(str[idx]) || '_' == str[idx] || ft_isdigit(str[idx]))
			idx++;
		else
			return (true);
	}
	return (false);
}

void	builtin_unset(t_data *d, t_cmd *node)
{
	int		arg;
	char	*pos_env_tab;
	
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	arg = 1;
	while (node->cmd_arg[arg])
	{
		if ((pos_env_tab = get_env_tab_pos(node->cmd_arg[arg], d->env)))
			d->env = remove_entry_from_env(d->env, pos_env_tab);
		arg++;
	}
}

char	**remove_entry_from_env(char **env, char *entry)
{
	int		len;
	int		idx;
	int		idx_new;
	char	**new_env_tab;

	len = 0;
	idx = 0;
	idx_new = 0;
	while (env[len])
		len++;
	new_env_tab = (char **) malloc(sizeof(char *) * len);
	while (env[idx])
	{
		if((0 == ft_strncmp(env[idx], entry, ft_strlen(entry))) && idx++)
			continue;
		new_env_tab[idx_new] = env[idx];
		idx++;
		idx_new++;
	}
	new_env_tab[len - 1] = NULL;
	free(env);
	free(entry);
	return (new_env_tab);
}

void	builtin_cd(t_data *d, t_cmd *node)
{
	char	*path_home;

	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	if (NULL == node->cmd_arg[1])
	{
		if((path_home = env_value(d, "HOME")))
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
			bash_msg3(\
			"bash: cd: ", node->cmd_arg[1], ": Permission denied");
		else if (ENOENT  == errno)
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
	if (((0 == ft_strncmp(node->cmd_arg[1], "-n", 2)) && arg++))
		new_line = false;
	while(node->cmd_arg[arg])
	{
		write(fd, node->cmd_arg[arg], ft_strlen(node->cmd_arg[arg]));
		if (node->cmd_arg[arg + 1])
			write(fd, " ", 1);
		else (new_line)
			write(fd, "\n", 1);
		arg++;
	}
	close(d->pip_out[WRITE]);
}