/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut_user_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:40:39 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 10:05:51 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cut_user_input(t_data *d)
{
	if ('<' == d->user_input[0] && '<' == d->user_input[1])
		cut_input_add_list(d, HEREDOC, 2);
	else if ('<' == d->user_input[0])
		cut_input_add_list(d, FILE_IN, 1);
	else if ('>' == d->user_input[0] && '>' == d->user_input[1])
		cut_input_add_list(d, FILE_APPEND, 2);
	else if ('>' == d->user_input[0])
		cut_input_add_list(d, FILE_OUT, 1);
	else if ('|' == d->user_input[0])
		cut_input_add_list(d, PIPE, 1);
	else
		cut_input_add_list(d, WORD, 0);
}

void	cut_input_add_list(t_data *d, int id, int skip)
{
	char	*word;
	char	*tmp;

	tmp = ft_strdup(&(d->user_input[skip]));
	free(d->user_input);
	d->user_input = tmp;
	trim_str(&(d->user_input), " ");
	word = word_from_input(d, id);
	add_node_token(d, id, word);
	d->user_input = rest_from_input(d, id, word);
}

char	*rest_from_input(t_data *d, int id, const char *word)
{
	char	*word_rest;

	if (PIPE == id)
		word_rest = d->user_input;
	else
		word_rest = &(d->user_input[ft_strlen(word)]);
	word_rest = ft_strdup(word_rest);
	trim_str(&word_rest, " ");
	if ('\0' == word_rest[0])
	{
		free(word_rest);
		word_rest = NULL;
	}
	free(d->user_input);
	return (word_rest);
}

char	*word_from_input(t_data *d, int id)
{
	int 	len;
	int		len_quote;
	char	*word;

	len = 0;
	while (NULL == ft_strchr(" <|>", d->user_input[len]))
	{
		len_quote = match_quote_idx(&(d->user_input[len]));
		if (len_quote)
			len += len_quote;
		else
			len++;
	}
	if (PIPE == id)
		word = NULL;
	else
		word = ft_substr(d->user_input, 0, len);
	return (word);
}

// | > f_out"hello" arg >>append arg | cmd arg|
// char	*rest_from_input(t_data *d, int rest_start)
// {
// 	int 	rest_len;
// 	char	*word_rest;

// 	rest_len = ft_strlen(d->user_input);
// 	word_rest = ft_substr(d->user_input, rest_start, rest_len);
// 	printf("rest_start: %d |%s|\n", rest_start, word_rest);
// 	trim_str(&word_rest, " ");
// 	if ('\0' == word_rest[0])
// 	{
// 		free(word_rest);
// 		word_rest = NULL;
// 	}
// 	free(d->user_input);
// 	return (word_rest);
// }

/*returns the length of an matching quoted string, if no match then 0*/
int	match_quote_idx(const char *str)
{
	int		idx;
	char	quote;

	idx= 1;
	if ('"' == *str || '\'' == *str)
	{
		quote = str[0];
		while (str[idx])
		{
			if (str[idx] == quote)
				return ++idx;
			idx++;
		}
	}
	return 0;
}
