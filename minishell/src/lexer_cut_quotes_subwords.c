/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut_quotes_subwords.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:47:44 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 10:16:59 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cut_quotes_subwords(t_sub_list **node_s, char *word)
{
	int		idx;
	int		idx_start;
	int		len_quote;
	bool	word_before_quote;

	idx = 0;
	idx_start = 0;
	word_before_quote = true;
	while (word[idx])
	{
		if ((len_quote = match_quote_idx(&(word[idx]))))
		{
			if (0 < idx && word_before_quote)
				add_str_node_s_word(word, node_s, idx_start, idx);
			word_before_quote = false;
			add_quo_node_s_word(word, node_s, idx, len_quote - 1);
			idx_start = idx + len_quote;
			idx += len_quote;
		}
		else
			idx++;
	}
	if (idx_start != idx)
		add_str_node_s_word(word, node_s, idx_start, idx - idx_start);
}

void	add_str_node_s_word(char *word, t_sub_list **node_s, int start, int len)
{
	char	*sub_word;
	int		id;

	sub_word = ft_substr(word, start, len);
	id = STRING;
	add_node_sub_word(node_s, id, sub_word);
}

void	add_quo_node_s_word(char *word, t_sub_list **node_s, int start, int len)
{
	char	*sub_word;
	int		id;

	id = UNPROCESSED;
	sub_word = NULL;
	if ('\'' == word[start])
	{
		sub_word = ft_substr(word, start + 1, len - 1);
		id = QUOTE_SINGLE;
	}
	else if ('"' == word[start])
	{
		sub_word = ft_substr(word, start + 1, len - 1);
		id = QUOTE_DOUBLE;
	}
	add_node_sub_word(node_s, id, sub_word);
}
