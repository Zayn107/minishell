/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:55:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/12 19:31:31 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	free_all(t_data *d)
// {
// 	// free_tab(d->tab_env_cmd_path);
// 	free_list(d->list_cmd);
// 	free(d->user_input);
// 	d->user_input = NULL;
// }

void	free_tab(char **tab)
{
	int	idx;

	idx = 0;
	if (tab)
	{
		while (tab[idx])
		{
			// printf("free: %s\n", tab[idx]);
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
	free(d->user_input);
	free_list_token_and_subword(d->list_token);
}

/*free a list where the end is marked with an NULL pointer*/
// void	free_list(t_cmd *list_cmd)
// {
// 	t_cmd	*current;
// 	t_cmd	*tmp;

// 	if (list_cmd)
// 	{
// 		current = list_cmd;
// 		while (current->next != NULL)
// 		{
// 			tmp = current;
// 			current = current->next;
// 			free(tmp->cmd_path);
// 			tmp->cmd_path = NULL;
// 			free_tab(tmp->cmd_arg);
// 			free(tmp);
// 			tmp = NULL;
// 		}
// 		free(current->cmd_path);
// 		current->cmd_path = NULL;
// 		free_tab(current->cmd_arg);
// 		free(current);
// 		current = NULL;
// 	}
// }
