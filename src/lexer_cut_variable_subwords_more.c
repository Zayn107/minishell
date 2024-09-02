/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut_variable_subwords_more.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:37:13 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 16:20:45 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_variable(t_sub_list *cur)
{
	char		*tmp;
	char		*idx_var;

	tmp = ft_strdup(cur->sub_word);
	free(cur->sub_word);
	cur->sub_word = NULL;
	cur->sub_id = UNPROCESSED;
	idx_var = ft_strchr(tmp, '$');
	while (NULL != tmp && idx_var)
	{
		idx_var = ft_strchr(tmp, '$');
		if (NULL == idx_var)
			break ;
		if (tmp != idx_var)
			cut_string_before_var(&cur, &tmp, idx_var);
		else if ('?' == idx_var[1])
			cut_var_exit(&cur, &tmp);
		else if ('_' == idx_var[1] || ft_isalpha(idx_var[1]))
			cut_var(&cur, &tmp, idx_var);
		else
			cut_invalid_var(&cur, &tmp, idx_var);
	}
	add_remaining_string(&cur, &tmp);
}
