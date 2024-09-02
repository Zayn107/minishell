/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut_quotes_subwords.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:47:44 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 15:41:36 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//cut word into subwords, matching quotes, strings, space is not removed
void	cut_quotes_subwords(t_sub_list **node_s, char *word)
{
	int		idx;
	int		end_last_word;
	int		len_q;

	idx = 0;
	end_last_word = 0;
	while (word[idx])
	{
		len_q = matching_quote_len(&(word[idx]));
		if (len_q)
		{
			if (end_last_word < idx)
				add_str_node_s_word(\
					word, node_s, end_last_word, idx - end_last_word);
			add_quo_node_s_word(word, node_s, idx, len_q - 1);
			idx += len_q;
			end_last_word = idx;
		}
		else
			idx++;
	}
	if (word[end_last_word])
		add_str_node_s_word(word, node_s, end_last_word, idx);
}

//create and add a new node to subword list with the ID of WORD
void	add_str_node_s_word(char *word, t_sub_list **node_s, int start, int len)
{
	char	*sub_word;
	int		id;

	sub_word = ft_substr(word, start, len);
	id = STRING;
	add_node_sub_word(node_s, id, sub_word);
}

//create and add a new node to subword list with ID QUOTE_SINGLE / QUOTE_DOUBLE
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
