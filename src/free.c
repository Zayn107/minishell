/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:55:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 12:31:25 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	idx;

	idx = 0;
	if (tab)
	{
		while (tab[idx])
		{
			free(tab[idx]);
			tab[idx] = NULL;
			idx++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_list_token_and_subword(t_token *head)
{
	t_token	*current;
	t_token	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->word);
		if (tmp->list_sub_word)
			free_list_sub_word(tmp->list_sub_word);
		tmp->word = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_list_sub_word(t_sub_list *head)
{
	t_sub_list	*current;
	t_sub_list	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->sub_word);
		tmp->sub_word = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_all_except_env(t_data *d)
{
	remove_tmp_files(d->list_cmd);
	free(d->user_input);
	d->user_input = NULL;
	free_list_token_and_subword(d->list_token);
	free_cmd_list(d->list_cmd);
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*node;
	t_cmd	*tmp;
	int		idx;

	node = head;
	while (node)
	{
		idx = 0;
		while (node->cmd_arg[idx])
		{
			free(node->cmd_arg[idx]);
			node->cmd_arg[idx] = NULL;
			idx++;
		}
		free(node->cmd_arg);
		node->cmd_arg = NULL;
		free(node->cmd_path);
		free(node->file_in);
		free(node->file_out);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}