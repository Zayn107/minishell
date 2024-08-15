/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 13:05:01 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* do not use the "cat" cmd for testing, if it has no input it will stack!!*/
 
#include "../include/minishell.h"

int	main(const int argc, char *argv[], char *arge[])
{
	t_data	data;
	(void) argc;
	(void) argv;

	copy_env(&data, arge);
	while (prompt_user(&data))
		;
	free_tab(data.env);
}

bool	prompt_user(t_data *d)
{
	init_data(d);
	// prompt input
	// d->user_input = readline("MINISHELL=> ");
	// TEST VAR
	d->user_input = ft_strdup("$ $? $HOME $HOME\"str\"txt $not_exist $6 $! '$?' str\"$HOME\"");
	// d->user_input = ft_strdup("> txt'hello'\"$HOME text\"");
	// d->user_input = ft_strdup("$< <file_in>file_\"out\" arg$HOME>>append arg$|cmd$? arg$_not_valid");
	// d->user_input = ft_strdup("> out1 >> app1 cmd arg < file_new arg << E");
	// d->user_input = ft_strdup(" >> append");
	// d->user_input = ft_strdup("< heredod\"$HOME\"$ cmd arg arg | new_cmd '$?'");
	
	// print user input
	printf("user_input: |%s|\n", d->user_input);
	trim_str(&(d->user_input), " ");
	if (invalid_user_input(d->user_input))
		return true;  // TODO: add free all to return
	lexer(d);
	// if (invalid_token(d))
	// 	return false; //TODO change later to return true, restart loop
	// cmd_list_from_token(d, true);


	// print_tab(d->env);
	print_token_list(d->list_token, true);
	// print_cmd_list(d->list_cmd);
	free_list_token_and_subword(d->list_token);
	return (false);
}

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
	if (0 == access(c_node->f_out, F_OK))
		if (-1 == access(c_node->f_out, W_OK | R_OK))
			return bash_msg(c_node->f_out, ": Permission denied");
	c_node->fd_f_out = open(t_node->word, O_CREAT | O_APPEND, 0664);
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_append'");
	return (true);
}

/*if file exist, check if read ok and open with fd flag 'read only', otherwise
return false, else if not exist, create file with fd 'read only' flag*/
bool	get_file_out(t_cmd *c_node, t_token *t_node)
{
	errno = 0;
	free_old_direction(c_node, t_node->id);
		c_node->f_out = ft_strdup(t_node->word);
	if (0 == access(c_node->f_out, F_OK))
		if (-1 == access(c_node->f_out, W_OK))
			return bash_msg(c_node->f_out, ": Permission denied");
	c_node->fd_f_out = open(t_node->word, O_CREAT | O_WRONLY, 0664);
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

	current = d->list_token;
	invalid = false;
	while (current && !invalid)
	{
		if (PIPE == current->id && NULL == current->prev)
			invalid = !bash_msg1("`|'", "syntax error near unexpected token ");
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
