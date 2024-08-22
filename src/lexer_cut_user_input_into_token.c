/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut_user_input_into_token.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:19:31 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/22 15:14:22 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//str must be trimmed, based on first character, ID is decided
void	cut_user_input_into_token(t_data *d)
{
	if ('<' == d->user_input[0] && '<' == d->user_input[1])
		cut_input_add_list_token(d, HEREDOC, 2);
	else if ('<' == d->user_input[0])
		cut_input_add_list_token(d, FILE_IN, 1);
	else if ('>' == d->user_input[0] && '>' == d->user_input[1])
		cut_input_add_list_token(d, FILE_APPEND, 2);
	else if ('>' == d->user_input[0])
		cut_input_add_list_token(d, FILE_OUT, 1);
	else if ('|' == d->user_input[0])
		cut_input_add_list_token(d, PIPE, 1);
	else
		cut_input_add_list_token(d, WORD, 0);
}

//cut id character from input, add id and next word to token node, rest to input
void	cut_input_add_list_token(t_data *d, int id, int skip)
{
	char	*word;

	d->user_input = cut_str(d->user_input, skip);
	trim_str(&(d->user_input), " ");
	word = word_after_skip(d, id);
	add_node_token(d, id, word);
	d->user_input = rest_from_input(d, word);
}

//mallocs str word (matching quotes), NULL if ID PIPE or len 0 to next delimiter
char	*word_after_skip(t_data *d, int id)
{
	int 	len;
	int		len_quote;
	char	*word;

	len = 0;
	while (NULL == ft_strchr(" <|>", d->user_input[len]))
	{
		len_quote = matching_quote_len(&(d->user_input[len]));
		if (len_quote)
			len += len_quote;
		else
			len++;
	}
	if (PIPE == id || !len)
		word = NULL;
	else
		word = ft_substr(d->user_input, 0, len);
	return (word);
}

//subtract "word" from input, trim input, if nothing left free and set to NULL
char	*rest_from_input(t_data *d, const char *word)
{
	char	*word_rest;

	if (NULL == word)
	{
		if (ft_strlen(d->user_input))
			return (d->user_input);
		else
			free(d->user_input);
	}
	else
	{
		word_rest = cut_str(d->user_input, ft_strlen(word));
		trim_str(&word_rest, " ");
		if (ft_strlen(word_rest))
			return (word_rest);
		free(word_rest);
	}
	return (NULL);
}
