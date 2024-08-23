/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_direct_files.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:45:17 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/23 11:29:46 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	get_file_in(t_cmd *c_node, t_token *t_node)
{
	errno = 0;
	free_old_direction(c_node, t_node->id);
	c_node->file_in = ft_strdup(t_node->word);
	if (-1 == access(c_node->file_in, F_OK))
		return bash_msg(c_node->file_in, ": No such file or directory");
	else if (-1 == access(c_node->file_in, R_OK))
		return bash_msg(c_node->file_in, ": Permission denied");
	c_node->fd_in = open(t_node->word, O_RDONLY);
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_file_in'");
	return (true);
}

bool	get_heredoc_input(t_cmd *n_cmd, t_token *n_token)
{
	char	*buffer;
	char	*delimiter;

	errno = 0;
	free_old_direction(n_cmd, n_token->id);
	delimiter = n_token->word;
	n_cmd->file_in = create_heredoc_fname(&(n_cmd->is_tmp_file_in));
	n_cmd->is_tmp_file_in = true;
	n_cmd->fd_in = open(n_cmd->file_in, O_CREAT | O_WRONLY, 0777);
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_heredoc_input'");
	while (true)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (0 == ft_strncmp(buffer, delimiter, ft_strlen(delimiter)))
			break ;
		write(n_cmd->fd_in, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(n_cmd->fd_in);
	n_cmd->fd_in = open(n_cmd->file_in, O_RDONLY, 0777);
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

/*if file exist, check if read and write ok and open with fd flag "append", otherwise return false, else if not exist, create file with fd "append" flag*/
bool	get_append(t_cmd *c_node, t_token *t_node)
{
	errno = 0;
	free_old_direction(c_node, t_node->id);
		c_node->file_out = ft_strdup(t_node->word);
	c_node->fd_out = open(t_node->word, O_CREAT | O_APPEND, 0664);
	if (0 == access(c_node->file_out, F_OK))
	{
		if (-1 == access(c_node->file_out, W_OK | R_OK))
			return bash_msg(c_node->file_out, ": Permission denied");
	}
	else
		return bash_msg(c_node->file_out, ": No such file or directory");
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
		c_node->file_out = ft_strdup(t_node->word);
	c_node->fd_out = open(t_node->word, O_CREAT | O_WRONLY, 0664);
	if (0 == access(c_node->file_out, F_OK))
	{
		if (-1 == access(c_node->file_out, W_OK))
			return bash_msg(c_node->file_out, ": Permission denied");
	}
	else
		return bash_msg(c_node->file_out, ": No such file or directory");
	if (-1 == errno)
		return e_msg("Failed to open file in 'get_file_out'");
	return (true);
}