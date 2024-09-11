/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:43:54 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/11 15:23:39 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	delimiter_stop_writing(t_data *d, char *buffer, char *delimiter, int fd)
{
	t_doc	*doc_list;

	doc_list = NULL;
	if (0 == ft_strncmp(buffer, delimiter, ft_strlen(delimiter)))
	{
		free(buffer);
		return (true) ;
	}
	(void) fd;
	(void) d;
	cut_str_into_doc_list(buffer, &doc_list);
	evaluate_var_doc_list(d, &doc_list);
	buffer = join_doc_list(buffer, &doc_list);
	free_doc_list(&doc_list);
	write(fd, buffer, ft_strlen(buffer));
	free(buffer);
	return (false) ;
}

void	print_doc_list(t_doc **head)
{
	t_doc	*node;

	node = *head;
	printf("print doc list:\n");
	while (node)
	{
		printf("word: %s ", node->word);
		if (node->id == WORD)
			printf("WORD");
		else if (node->id == VAR)
			printf("VAR");
		else if (node->id == VAR_EXIT)
			printf("VAR_EXIT");
		else if (node->id == INV_VAR)
			printf("INV_VAR");
		printf("\n");
		node = node->next;
	}
}

void	free_doc_list(t_doc **head)
{
	t_doc	*node;
	t_doc	*tmp;

	node = *head;
	while (node)
	{
		if (NULL != node->word)
		{
			free(node->word);
			node->word = NULL;
		}
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

char	*join_doc_list(char *buffer, t_doc **head)
{
	t_doc	*node;
	bool	first_word;

	node = *head;
	first_word = true;
	free(buffer);
	while (node)
	{
		if (WORD == node->id)
		{
			if (first_word)
			{
				buffer = ft_strdup(node->word);
				first_word = false;
			}
			else
				buffer = join_free(&buffer, true, &(node->word), false);
		}
		node = node->next;
	}
	return (buffer);
}

void	cut_str_into_doc_list(char *str, t_doc **head)
{
	int		idx;
	int		start_str;
	int		start_var;
	char	*tmp;

	idx = 0;
	start_str = 0;
	while (str[idx])
	{
		if ('$' == str[idx] && ' ' != str[idx +1])
		{
			start_var = idx;
			if (start_str < start_var)
			{
				tmp = ft_substr(str, start_str, idx - start_str);
				add_node_doc(head, WORD, tmp);
			}
			idx++;
			if ('?' == str[idx])
			{
				idx++;
				tmp = ft_substr(str, start_var, idx - start_var);
				add_node_doc(head, VAR_EXIT, tmp);
			}
			else if ('_' == str[idx] || ft_isalpha(str[idx]))
			{
				idx++;
				while ('_' == str[idx] || ft_isalnum(str[idx]))
					idx++;
				tmp = ft_substr(str, start_var, idx - start_var);
				add_node_doc(head, VAR, tmp);
			}
			else
			{
				idx++;
				tmp = ft_substr(str, start_var, idx - start_var);
				add_node_doc(head, INV_VAR, tmp);
			}
			start_str = idx;
		}
		else
			idx++;
	}
	if (start_str < idx)
	{
		tmp = ft_substr(str, start_str, idx - start_str);
		// printf("inside cut_str: %s\n", tmp);
		add_node_doc(head, WORD, tmp);
	}
	// if (head != NULL)
	// 	printf("head is now %s\n", head->word);
}

void	evaluate_var_doc_list(t_data *d, t_doc **head)
{
	t_doc	*node;
	char	*tmp;

	node = *head;
	while (node)
	{
		if (VAR_EXIT == node->id)
		{
			free(node->word);
			tmp = ft_itoa(d->exit_status);
			node->word = ft_strdup(tmp);
			node->id = WORD;
			free(tmp);
		}
		else if (VAR == node->id)
		{
			if (has_var_name(d->env, &(node->word[1])))
			{
				tmp = node->word;
				node->word = env_value(d, &(node->word[1]));
				node->id = WORD;
				free(tmp);
			}
		}
		node = node->next;
	}
}

/*add a new node at the end of the "token list" */
void	add_node_doc(t_doc **head, int id, char *word)
{
	t_doc	*new_node;
	t_doc	*current;

	new_node = (t_doc *) malloc(sizeof(t_doc));
	new_node->id = id;
	new_node->word = word;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		new_node->prev = current;
		current->next = new_node;
	}
}