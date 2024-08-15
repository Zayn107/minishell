/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:13:55 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 12:10:07 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*add a new node at the end of the "token list" */
void	add_node_token(t_data *d, int id, char *word)
{
	t_token	*new_node;
	t_token	*current;

	new_node = (t_token *) malloc(sizeof(t_token));
	new_node->id = id;
	new_node->word = word;
	new_node->list_sub_word = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;

	if (d->list_token == NULL)
		d->list_token = new_node;
	else
	{
		current = d->list_token;
		while (current->next != NULL)
			current = current->next;
		new_node->prev = current;
		current->next = new_node;
	}
}

// void	insert_node_token_struct(t_token *current, int id, char *word)
// {
// 	t_token	*new_node;

// 	new_node = (t_token *) malloc(sizeof(t_token));
// 	new_node->id = id;
// 	new_node->word = word;
// 	new_node->list_sub_word = NULL;
// 	new_node->next = current->next;
// 	current->next = new_node;
// }

void	add_node_sub_word(t_sub_list **node, int sub_id, char *sub_word)
{
	t_sub_list	*new_node;
	t_sub_list	*current;

	new_node = (t_sub_list *) malloc(sizeof(t_sub_list));
	new_node->sub_id = sub_id;
	new_node->sub_word = sub_word;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (*node == NULL)
		*node = new_node;
	else
	{
		current = *node;
		while (current->next != NULL)
			current = current->next;
		new_node->prev = current;
		current->next = new_node;
	}
}

/*add node after*/
void	insert_node_sub_word(t_sub_list *node, int sub_id, char *sub_word)
{
	t_sub_list	*new_node;

	new_node = (t_sub_list *) malloc(sizeof(t_sub_list));
	new_node->sub_word = sub_word;
	new_node->sub_id = sub_id;
	new_node->prev = node;
	if (node->next)
		node->next->prev = new_node;
	new_node->next = node->next;
	node->next = new_node;
}

void	insert_before_node_sub_word(t_sub_list *node, int sub_id, char *sub_word)
{
	t_sub_list	*new_node;

	new_node = (t_sub_list *) malloc(sizeof(t_sub_list));
	new_node->sub_word = sub_word;
	new_node->sub_id = sub_id;
	new_node->prev = node->prev;
	new_node->next = node;
	if (node->prev)
		node->prev->next = new_node;
	node->prev = new_node;
}

/*add a new node at the end of the "cmd list" */
t_cmd	*add_node_cmd(t_data *d)
{
	t_cmd	*new_node;
	t_cmd	*current;

	new_node = (t_cmd *) malloc(sizeof(t_cmd));
	new_node->builtin_fun = NULL;
	new_node->cmd_arg = (char **) malloc(sizeof(char *) * 2);
	new_node->cmd_arg[0] = NULL;
	new_node->cmd_arg[1] = NULL;
	new_node->fd_f_in = FD_NONE;
	new_node->fd_f_out = FD_NONE;
	new_node->is_tmp_file_in = false;
	new_node->f_in = NULL;
	new_node->f_out = NULL;
	new_node->next = NULL;
	if (d->list_cmd == NULL)
		d->list_cmd = new_node;
	else
	{
		current = d->list_cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (new_node);
}
