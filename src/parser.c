/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:15:34 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/14 13:41:16 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	parser(t_data *d)
// {
// 	// t_token	*current;
//
// 	// current = d->list_token;
// 	// parse_cmd_arg(d);
// 	// while (current)
// 	// {
// 	// 	current = current->next;
// 	// }
// }

// void	parse_cmd_arg(t_data *d)
// {
// 	t_token	*current;
// 	bool	start;
// 	bool	found_cmd;
// 	int		count_word;

// 	current = d->list_token;
// 	set_start_values(&start, &found_cmd, &count_word);
// 	while (current)
// 	{
// 		count_word++;
// 		if (WORD != current->token)
// 			count_word = 0;
// 		else if (start || (2 == count_word && !found_cmd))
// 		{
// 			found_cmd = true;
// 			mark_and_add_cmd_arg_tab(current, d);
// 		}
// 		start = false;
// 		if (PIPE == current->token)
// 			set_start_values(&start, &found_cmd, &count_word);
// 		current = current->next;
// 	}
// }

// void	set_start_values(bool *start, bool *found_cmd, int *count_word)
// {
// 	*start = true;
// 	*found_cmd = false;
// 	*count_word = 0;
// }

// void	mark_and_add_cmd_arg_tab(t_token *current, t_data *d)
// {
// 	t_token	*next_cur;
// 	char	**tab_arg;
// 	t_cmd	*last_node;

// 	current->token = COMMAND;
// 	add_node_cmd(d);
// 	add_cmd_arg_tab(d, current->word);
// 	next_cur = current;
// 	if (next_cur->next)
// 		while ((next_cur = next_cur->next))
// 		{
// 			if (WORD == next_cur->token)
// 			{
// 				next_cur->token = ARGUMENT;
// 				add_cmd_arg_tab(d, next_cur->word);
// 			}
// 			else
// 				break;
// 		}
// }

// t_cmd	*last_cmd(t_cmd *head)
// {
// 	t_cmd	*current;

// 	current = head;
// 	while (current)
// 		current = current->next;
// 	return current;
// }

// /*find the last node in the "list_cmd", add "word" to the end of cmd_arg** */
// void	add_cmd_arg_tab(t_data *d, char *word)
// {
// 	char	**tmp;
// 	int		len;
// 	int		idx;
// 	t_cmd	*current;

// 	current = d->list_cmd;
// 	len = 0;
// 	idx = 0;
// 	while (current->next)
// 		current = current->next;
// 	if (current->cmd_arg)
// 		while (d->list_cmd->cmd_arg[len])
// 			len++;
// 	tmp = current->cmd_arg;
// 	current->cmd_arg = (char **) malloc(sizeof(char *) * (len + 2));
// 	if (tmp)
// 		while (tmp[idx])
// 		{
// 			current->cmd_arg[idx] = tmp[idx];
// 			idx++;
// 		}
// 	current->cmd_arg[idx] = ft_strdup(word);
// 	current->cmd_arg[idx + 1] = NULL;
// 	free(tmp);
// }

// t_cmd	*add_node_cmd(t_data *d)
// {
// 	t_cmd	*new_node;
// 	t_cmd	*current;

// 	new_node = (t_cmd *) malloc(sizeof(t_cmd));
// 	new_node->builtin_fun = NULL;
// 	new_node->cmd_path = NULL;
// 	new_node->cmd_arg = NULL;
// 	new_node->fd_file_in = FD_NONE;
// 	new_node->fd_f_out = FD_NONE;
// 	new_node->next = NULL;
// 	if (d->list_cmd == NULL)
// 		d->list_cmd = new_node;
// 	else
// 	{
// 		current = d->list_cmd;
// 		while (current->next != NULL)
// 			current = current->next;
// 		current->next = new_node;
// 	}
// 	return (new_node);
// }
