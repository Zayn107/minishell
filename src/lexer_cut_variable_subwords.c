/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut_variable_subwords.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:46:56 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 16:20:30 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*cut "non var string" before variable from '**tmp', write to node, id=STRING*/
void	cut_string_before_var(t_sub_list **cur, char **tmp, char *idx_var)
{
	int		len_str;
	char	*str_before;
	char	*str_rest;

	len_str = idx_var - *tmp;
	str_before = ft_substr(*tmp, 0, len_str);
	if (UNPROCESSED == (*cur)->sub_id)
	{
		(*cur)->sub_id = STRING;
		(*cur)->sub_word = str_before;
	}
	else
	{
		insert_node_sub_word(*cur, STRING, str_before);
		*cur = (*cur)->next;
	}
	str_rest = ft_strdup(&((*tmp)[len_str]));
	free(*tmp);
	*tmp = str_rest;
}

/*cut "$?" from '**tmp', write to node id=VAR_EXIT, sub_word=NULL*/
void	cut_var_exit(t_sub_list **cur, char **tmp)
{
	const int	len_exit_var = 2;
	char		*str_var;
	char		*str_rest;

	str_var = NULL;
	if (UNPROCESSED == (*cur)->sub_id)
	{
		(*cur)->sub_id = VAR_EXIT;
		(*cur)->sub_word = str_var;
	}
	else
	{
		insert_node_sub_word(*cur, VAR_EXIT, str_var);
		*cur = (*cur)->next;
	}
	str_rest = ft_strdup(&((*tmp)[len_exit_var]));
	free(*tmp);
	*tmp = str_rest;
}

/*cut variable name from '**tmp', id=VAR*/
void	cut_var(t_sub_list **cur, char **tmp, char *idx_var)
{
	char		*str_var;
	char		*str_rest;
	int			len;

	len = 2;
	while ('_' == idx_var[len] || ft_isalnum(idx_var[len]))
		len++;
	str_var = ft_substr(idx_var, 1, len - 1);
	if (UNPROCESSED == (*cur)->sub_id)
	{
		(*cur)->sub_id = VAR;
		(*cur)->sub_word = str_var;
	}
	else
	{
		insert_node_sub_word(*cur, VAR, str_var);
		*cur = (*cur)->next;
	}
	str_rest = ft_strdup(&(idx_var[len]));
	free(*tmp);
	*tmp = str_rest;
}

/*cut invalid var name from '**tmp', e.g. "$5hello" cut "$5" leave "hello"*/
void	cut_invalid_var(t_sub_list **cur, char **tmp, char *idx_var)
{
	int		idx_rest;
	char	*word;
	char	*str_rest;

	if (' ' == idx_var[1] || '\0' == idx_var[1])
	{
		idx_rest = 1;
		word = ft_strdup("$");
		if (UNPROCESSED == (*cur)->sub_id)
		{
			(*cur)->sub_id = STRING;
			(*cur)->sub_word = word;
		}
		else
		{
			insert_node_sub_word(*cur, STRING, word);
			*cur = (*cur)->next;
		}
	}
	else
		idx_rest = 2;
	str_rest = ft_strdup(&(idx_var[idx_rest]));
	free(*tmp);
	*tmp = str_rest;
}

/*remaining str after last var is passed to sub_word, else node is removed*/
void	add_remaining_string(t_sub_list **cur, char **tmp)
{
	if (*tmp && '\0' != (*tmp)[0])
	{
		if (UNPROCESSED == (*cur)->sub_id)
		{
			(*cur)->sub_id = STRING;
			(*cur)->sub_word = *tmp;
		}
		else
		{
			insert_node_sub_word(*cur, STRING, *tmp);
			*cur = (*cur)->next;
		}
	}
	else
		free(*tmp);
}
