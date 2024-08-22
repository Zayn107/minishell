/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:56:21 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/22 15:30:39 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*check if user input is empty, if true, free all, return true to keep loop*/
bool	invalid_user_input(t_data *d, char *user_input)
{
	int	idx;

	idx = 0;
	while (user_input[idx])
	{
		if (' ' != user_input[idx])
			return (false);
		idx++;
	}
	free_all_except_env(d);
	return true;
}

//if no word after redirection or before/after PIPE throw
bool	invalid_token(t_data *d)
{
	t_token	*current;
	char	*e_word;

	current = d->list_token;
	while (current)
	{
		if (PIPE == current->id && \
			(NULL == current->prev || NULL == current->next->word))
			{
			bash_msg1("`|'", "syntax error near unexpected token ");
			free_all_except_env(d);
			return (true);
			}
		else if (PIPE != current->id && NULL == current->word)
		{
			e_word = next_direction_character_or_new_line(current);
			bash_msg1(e_word, "syntax error near unexpected token ");
			free(e_word);
			free_all_except_env(d);
			return (true);
		}
		current = current->next;
	}
	return (false);
}

//malloc str of the next direction character for error msg
char	*next_direction_character_or_new_line(t_token *current)
{
	current = current->next;
	while (current)
	{
		if (FILE_OUT == current->id)
			return ft_strdup("`>'");
		else if (FILE_APPEND == current->id)
			return ft_strdup("`>>'");
		else if (PIPE == current->id)
			return ft_strdup("`|'");
		else if (HEREDOC == current->id)
			return ft_strdup("`<<'");
		else if (FILE_IN == current->id)
			return ft_strdup("`<'");
		current = current->next;
	}
	return ft_strdup("`newline'");
}