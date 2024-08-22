/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsorted_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:38:31 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/22 10:56:07 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	cmd_list_from_token(t_data *d, bool success)
{
	t_token	*cur_tok;
	t_cmd	*cur_cmd;

	cur_cmd = add_node_cmd(d);
	cur_tok = d->list_token;
	while (cur_tok && success)
	{
		if (PIPE == cur_tok->id)
			cur_cmd = add_node_cmd(d);
		else if (COMMAND == cur_tok->id)
			cur_cmd->cmd_arg[0] = ft_strdup(cur_tok->word);
		else if (ARGUMENT == cur_tok->id)
			assign_arg(&(cur_cmd->cmd_arg), cur_tok->word);
		else if (FILE_IN == cur_tok->id)
			success = get_file_in(cur_cmd, cur_tok);
		else if (HEREDOC == cur_tok->id)
			success = get_heredoc_input(cur_cmd, cur_tok);
		else if (FILE_APPEND == cur_tok->id)
			success = get_append(cur_cmd, cur_tok);
		else if (FILE_OUT == cur_tok->id)
			success = get_file_out(cur_cmd, cur_tok);
		cur_tok = cur_tok->next;
	}
	return (success);
}

bool	get_heredoc_input(t_cmd *n_cmd, t_token *n_token)
{
	char	*buffer;
	char	*delimiter;

	errno = 0;
	free_old_direction(n_cmd, n_token->id);
	delimiter = n_token->word;
	n_cmd->f_in = create_heredoc_fname(&(n_cmd->is_tmp_file_in));
	n_cmd->is_tmp_file_in = true;
	n_cmd->fd_f_in = open(n_cmd->f_in, O_CREAT | O_WRONLY, 0777);
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_heredoc_input'");
	while (true)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (0 == ft_strncmp(buffer, delimiter, ft_strlen(delimiter)))
			break ;
		write(n_cmd->fd_f_in, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(n_cmd->fd_f_in);
	n_cmd->fd_f_in = open(n_cmd->f_in, O_RDONLY, 0777);
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_heredoc_input'");
	return (true);
}

char	*create_heredoc_fname(bool *is_tmp_file_in)
{
	int		n;
	char	*fname;
	char	*serial;

	n = 0;
	fname = NULL;
	while(NULL == fname)
	{
		serial = ft_itoa(n++);
		fname = ft_strjoin("tmp_heredoc_", serial);
		free(serial);
		if (0 == access(fname, F_OK))
		{
			free(fname);
			fname = NULL;
		}
	}
	*is_tmp_file_in = true;
	return (fname);
}

void	free_old_direction(t_cmd *node, int id)
{
	if (HEREDOC == id || FILE_IN == id)
	{
		if (FD_NONE != node->fd_f_in)
			close(node->fd_f_in);
		node->fd_f_in = FD_NONE;
		if (node->is_tmp_file_in)
			if (unlink(node->f_in))
				perror("unlink() error");
		node->is_tmp_file_in = false;
		free(node->f_in);
		node->f_in = NULL;
	}
	else if (FILE_APPEND == id || FILE_OUT == id)
	{
		if (FD_NONE != node->fd_f_out)
			close(node->fd_f_out);
		node->fd_f_out = FD_NONE;
		free(node->f_out);
		node->f_out = NULL;
	}
}

void	print_fd(int fd)
{
	char	*buffer;

	// fd = open("heredoc", O_RDONLY);
	// printf("fd in printf: %d\n", fd);
	printf("--- hello from print_fd\n");
	while (true)
	{
		buffer = get_next_line(fd);
		if (NULL == buffer)
		{
			printf("buffer is NULL\n");
			break ;
		}
		// write(1, buffer, ft_strlen(buffer));
		printf("%s", buffer);
		free(buffer);
	}
}


bool	get_file_in(t_cmd *c_node, t_token *t_node)
{
	errno = 0;
	free_old_direction(c_node, t_node->id);
	c_node->f_in = ft_strdup(t_node->word);
	if (-1 == access(c_node->f_in, F_OK))
		return bash_msg(c_node->f_in, ": No such file or directory");
	else if (-1 == access(c_node->f_in, R_OK))
		return bash_msg(c_node->f_in, ": Permission denied");
	c_node->fd_f_in = open(t_node->word, O_RDONLY);
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_file_in'");
	return (true);
}

/*if file exist, check if read and write ok and open with fd flag "append", otherwise return false, else if not exist, create file with fd "append" flag*/
bool	get_append(t_cmd *c_node, t_token *t_node)
{
	errno = 0;
	free_old_direction(c_node, t_node->id);
		c_node->f_out = ft_strdup(t_node->word);
	c_node->fd_f_out = open(t_node->word, O_CREAT | O_APPEND, 0664);
	if (0 == access(c_node->f_out, F_OK))
	{
		if (-1 == access(c_node->f_out, W_OK | R_OK))
			return bash_msg(c_node->f_out, ": Permission denied");
	}
	else
		return bash_msg(c_node->f_out, ": No such file or directory");
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_append'");
	return (true);
}

/*if file exist, check if read ok and open with fd flag 'read only', otherwise
return false, else if not exist, create file with fd 'read only' flag. Unless
directory in the path dose not exist.*/
bool	get_file_out(t_cmd *c_node, t_token *t_node)
{
	errno = 0;
	free_old_direction(c_node, t_node->id);
		c_node->f_out = ft_strdup(t_node->word);
	c_node->fd_f_out = open(t_node->word, O_CREAT | O_WRONLY, 0664);
	if (0 == access(c_node->f_out, F_OK))
	{
		if (-1 == access(c_node->f_out, W_OK))
			return bash_msg(c_node->f_out, ": Permission denied");
	}
	else
		return bash_msg(c_node->f_out, ": No such file or directory");
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_file_out'");
	return (true);
}

void	assign_arg(char ***cmd_arg, char *new_arg)
{
	int		idx_new_arg;
	int		idx;
	char	**tmp;

	idx_new_arg = 1;
	while (NULL != (*cmd_arg)[idx_new_arg])
		idx_new_arg++;
	tmp = (char **) malloc(sizeof(char *) * (idx_new_arg + 2));
	idx = 0;
	while (idx < idx_new_arg)
	{
		tmp[idx] = (*cmd_arg)[idx];
		idx++;
	}
	tmp[idx_new_arg] = ft_strdup(new_arg);
	tmp[idx_new_arg + 1] = NULL;
	free(*cmd_arg);
	*cmd_arg = tmp;
}

bool	create_file_if_not_exist(t_token *head)
{
	t_token	*current;
	int		fd;

	current = head;
	while (current)
	{
		fd = 0;
		if (FILE_OUT == current->id)
			fd = open(current->word, O_CREAT | O_WRONLY, 0664);
		else if (FILE_APPEND == current->id)
			fd = open(current->word, O_CREAT | O_APPEND, 0664);
		if (fd)
		{
			printf("fd: %d word: %s\n", fd, current->word);
			if (-1 == fd)
			{
				p_color(E_STY, E_BAC, E_COL, "bash: ");
				p_color(E_STY, E_BAC, E_COL, current->word);
				p_color(E_STY, E_BAC, E_COL, ": No such file or directory\n");
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

bool	invalid_token(t_data *d)
{
	t_token	*current;
	char	*e_word;
	bool	invalid;
	char	*buffer;

	current = d->list_token;
	invalid = false;
	while (current && !invalid)
	{
		if (PIPE == current->id && \
			(NULL == current->prev || NULL == current->next->word))
			invalid = !bash_msg1("`|'", "syntax error near unexpected token ");
		else if (PIPE == current->id && NULL == current->next)
		{
			buffer = get_next_line(STDIN_FILENO);
			printf("print buffer: %s|\n", buffer);
		}
		else if (PIPE != current->id && NULL == current->word)
		{
			e_word = next_meta_character_or_new_line(current);
			invalid = !bash_msg1(e_word, "syntax error near unexpected token ");
			free(e_word);
			free_all_except_env(d);
		}
		current = current->next;
	}
	return (invalid);
}

/*trim user input from white space, if pipe is last character then prompt for
input as long user enters none white space and | is not last, join all strs*/
void	prompt_if_pipe_last(t_data *d)
{
	char	*buf;

	buf = NULL;
	if ('|' == d->user_input[ft_strlen(d->user_input) - 1])
	{
		while (NULL == buf)
		{
			write(1, "> ", 2);
			buf = get_next_line(STDIN_FILENO);
			trim_str(&buf, "\n ");
			if (0 == ft_strlen(buf))
			{
				free(buf);
				buf = NULL;
			}
			else if ('|' == buf[ft_strlen(buf) - 1])
				d->user_input = join_free(&(d->user_input), true, &buf, true);
		}
		d->user_input = join_free(&(d->user_input), true, &buf, true);
	}
}

char	*next_meta_character_or_new_line(t_token *current)
{
	current = current->next;
	while (current)
	{
		if (FILE_OUT == current->id)
			return ft_strdup("`>'");
		else if (FILE_APPEND == current->id)
			return ft_strdup("`>>'");
		else if (PIPE == current->id)
			return ft_strdup("`|'");
		else if (HEREDOC == current->id)
			return ft_strdup("`<<'");
		else if (FILE_IN == current->id)
			return ft_strdup("`<'");
		current = current->next;
	}
	return ft_strdup("`newline'");
}

void	create_direct_out_files_if_not_exist(t_data *d)
{
	t_token	*current;

	current = d->list_token;
	while (current)
	{
		if (FILE_OUT)
		current = current->next;
	}
}

/*check if user input is empty*/
bool	invalid_user_input(char *user_input)
{
	if ('\0' == user_input[0])
		return true;
	return false;
}

void	init_data(t_data *d)
{
	d->user_input = NULL;
	d->list_token = NULL;
	// d->env = NULL;
	d->list_cmd = NULL;
	d->last_cmd = false;
	d->exit_status = 0;
	errno = 0;
}