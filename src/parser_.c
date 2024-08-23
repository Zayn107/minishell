/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:43:15 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/23 16:12:18 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	parser(t_data *d, bool success)
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
			assign_cmd(d, cur_cmd, cur_tok->word);
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

/*assign command to structure*/
void	assign_cmd(t_data *d, t_cmd *node, char *cmd)
{
	node->cmd_arg[0] = ft_strdup(cmd);
	node->cmd_path = find_cmd_path(d, cmd);
}

char	*find_cmd_path(t_data *d, char *cmd)
{
	char	*env_path;
	char	*cmd_path;
	char	*slash;
	char	**env_tab;
	int		idx;

	if ((NULL != ft_strrchr(cmd, '/')))
		return (ft_strdup(cmd));
	env_path = env_value(d, "PATH");
	if (NULL == env_path)
		return (NULL);
	env_tab = ft_split(env_path, ':');
	free(env_path);
	slash = ft_strdup("/");
	idx = 0;
	while (env_tab[idx])
	{
		cmd_path = join_free(&(env_tab[idx]), false, &slash, false);
		cmd_path = join_free(&(cmd_path), true, &(cmd), false);
		if ((0 == access(cmd_path, F_OK)))
			break;
		free(cmd_path);
		cmd_path = NULL;
		idx++;
	}
	free(slash);
	free_tab(env_tab);
	return (cmd_path);
}

void	free_old_direction(t_cmd *node, int id)
{
	if (HEREDOC == id || FILE_IN == id)
	{
		if (FD_NONE != node->fd_in)
			close(node->fd_in);
		node->fd_in = FD_NONE;
		if (node->is_tmp_file_in)
			if (unlink(node->file_in))
				perror("unlink() error");
		node->is_tmp_file_in = false;
		free(node->file_in);
		node->file_in = NULL;
	}
	else if (FILE_APPEND == id || FILE_OUT == id)
	{
		if (FD_NONE != node->fd_out)
			close(node->fd_out);
		node->fd_out = FD_NONE;
		free(node->file_out);
		node->file_out = NULL;
	}
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

void	init_data(t_data *d)
{
	d->user_input = NULL;
	d->list_token = NULL;
	d->list_cmd = NULL;
	d->exit_status = 0;
	errno = 0;
}
