/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_direct_files.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:45:17 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 21:29:00 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_file_in(t_data *d, t_cmd *c_node, t_token *t_node)
{
	if (-1 == access(t_node->word, F_OK))
	{
		d->exit_status = 1;
		c_node->valid = false;
		e_msg1(t_node->word, ": No such file or directory");
	}
	else if (-1 == access(t_node->word, R_OK))
	{
		d->exit_status = 1;
		c_node->valid = false;
		e_msg1(t_node->word, ": Permission denied");
	}
	else
	{
		free_old_direction(c_node, t_node->id);
		c_node->fd_in = open(t_node->word, O_RDONLY);
		c_node->file_in = ft_strdup(t_node->word);
	}
}

void	get_heredoc_input(t_cmd *c_node, t_token *t_node, char *delimiter)
{
	char	*buffer;

	errno = 0;
	free_old_direction(c_node, t_node->id);
	c_node->file_in = create_heredoc_fname(&(c_node->is_tmp_file_in));
	c_node->is_tmp_file_in = true;
	c_node->fd_in = open(c_node->file_in, O_CREAT | O_WRONLY, 0777);
	if (-1 == errno)
		return (perror("Failed to open file in 'get_heredoc_input'"));
	while (true)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (NULL == buffer)
			break ;
		if (0 == ft_strncmp(buffer, delimiter, ft_strlen(delimiter)))
			break ;
		write(c_node->fd_in, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(c_node->fd_in);
	c_node->fd_in = open(c_node->file_in, O_RDONLY, 0777);
	if (-1 == errno)
		perror("Failed to open file in 'get_heredoc_input'");
}

char	*create_heredoc_fname(bool *is_tmp_file_in)
{
	int		n;
	char	*fname;
	char	*serial;

	n = 0;
	fname = NULL;
	while (NULL == fname)
	{
		serial = ft_itoa(n++);
		fname = ft_strjoin(".tmp_heredoc_", serial);
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

/*if file exist, check if read and write ok and open with fd flag "append",
otherwise return false, else if not exist, create file with fd "append" flag*/
void	get_append(t_data *d, t_cmd *c_node, t_token *t_node)
{
	if (0 == access(t_node->word, F_OK))
	{
		if (-1 == access(t_node->word, W_OK))
		{
			d->exit_status = 1;
			c_node->valid = false;
			e_msg1(t_node->word, ": Permission denied");
			return ;
		}
	}
	free_old_direction(c_node, t_node->id);
	c_node->file_out = ft_strdup(t_node->word);
	c_node->fd_out = open(t_node->word, O_CREAT | O_APPEND | O_RDWR, 0664);
}

/*if file exist, check if read ok and open with fd flag 'read only', otherwise
return false, else if not exist, create file with fd 'read only' flag. Unless
directory in the path dose not exist.*/
void	get_file_out(t_data *d, t_cmd *c_node, t_token *t_node)
{
	if (0 == access(t_node->word, F_OK))
	{
		if (-1 == access(t_node->word, W_OK))
		{
			d->exit_status = 1;
			c_node->valid = false;
			e_msg1(t_node->word, ": Permission denied");
			return ;
		}
	}
	free_old_direction(c_node, t_node->id);
	c_node->file_out = ft_strdup(t_node->word);
	c_node->fd_out = open(t_node->word, O_CREAT | O_WRONLY | O_TRUNC, 0664);
}
