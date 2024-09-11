/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var_cut_str_doc_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:24:51 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/11 16:36:26 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cut_str_into_doc_list(char *str, t_doc **head, int sta_str, int sta_var)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if ('$' == str[idx] && ' ' != str[idx +1])
		{
			sta_var = idx;
			if (sta_str < sta_var)
				add_word_to_doc_list(head, str, idx, sta_str);
			idx++;
			if ('?' == str[idx])
				idx = add_var_exit_to_doc_list(head, str, idx, sta_var);
			else if ('_' == str[idx] || ft_isalpha(str[idx]))
				idx = add_var_to_doc_list(head, str, idx, sta_var);
			else
				idx = add_inv_var_to_doc_list(head, str, idx, sta_var);
			sta_str = idx;
		}
		else
			idx++;
	}
	if (sta_str < idx)
		add_word_to_doc_list(head, str, idx, sta_str);
}

void	add_word_to_doc_list(t_doc **head, char *str, int idx, int start_str)
{
	char	*tmp;

	tmp = ft_substr(str, start_str, idx - start_str);
	add_node_doc(head, WORD, tmp);
}

int	add_var_exit_to_doc_list(t_doc **head, char *str, int idx, int start_var)
{
	char	*tmp;

	idx++;
	tmp = ft_substr(str, start_var, idx - start_var);
	add_node_doc(head, VAR_EXIT, tmp);
	return (idx);
}

int	add_var_to_doc_list(t_doc **head, char *str, int idx, int start_var)
{
	char	*tmp;

	idx++;
	while ('_' == str[idx] || ft_isalnum(str[idx]))
		idx++;
	tmp = ft_substr(str, start_var, idx - start_var);
	add_node_doc(head, VAR, tmp);
	return (idx);
}

int	add_inv_var_to_doc_list(t_doc **head, char *str, int idx, int start_var)
{
	char	*tmp;

	idx++;
	tmp = ft_substr(str, start_var, idx - start_var);
	add_node_doc(head, INV_VAR, tmp);
	return (idx);
}
