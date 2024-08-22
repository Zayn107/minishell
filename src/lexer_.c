/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:06:18 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/22 13:54:16 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The Lexer is breaking the user input into its smallest building blocks,
1. redirections: '<', '<<', '|', '>>', '>';
2. words:			strings, quotes, variable.
Words are further broken down into subwords (to evaluate variables,
remove quotes) and after joined back together.*/

#include "../include/minishell.h"

/*cut "user input" into token (words) & subwords so that var. can be evaluated*/
void	lexer(t_data *d)
{
	t_token	*current;
	bool	found_cmd;

	found_cmd = false;
	trim_str(&(d->user_input), " ");
	prompt_if_pipe_last(d);
	while (d->user_input)
		cut_user_input_into_token(d);
	current = d->list_token;
	while (current)
	{
		if (PIPE != current->id && NULL != current->word)
		{
			cut_quotes_subwords(&(current->list_sub_word), current->word);
			cut_variable_subwords(&(current->list_sub_word), current->id);
			evaluate_variable_subwords(d, &(current->list_sub_word));
			join_subwords(&(current->list_sub_word), &current);
		}
		found_cmd = mark_word_cmd_arg(current, found_cmd);
		current = current->next;
	}
}

//cut subwords further into variables, remove if not valid name, except HEREDOC
void	cut_variable_subwords(t_sub_list **head,  int id_token)
{
	t_sub_list	*cur;
	char		*tmp;
	char		*idx_var;

	cur = *head;
	while (cur && HEREDOC != id_token)
	{
		if (QUOTE_DOUBLE == cur->sub_id || STRING == cur->sub_id)
		{
			tmp = ft_strdup(cur->sub_word);
			free(cur->sub_word);
			cur->sub_word = NULL;
			cur->sub_id = UNPROCESSED;
			while (NULL != tmp && (idx_var = ft_strchr(tmp, '$')))
			{
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
		cur = cur->next;
	}
}

/*replace var name with value if found "d.env", otherwise removed */
void	evaluate_variable_subwords(t_data *d, t_sub_list **head)
{
	t_sub_list	*cur;
	char		*tmp;

	cur = *head;
	while (cur)
	{
		if (VAR_EXIT == cur->sub_id)
			cur->sub_word = ft_itoa(d->exit_status);
		else if (VAR == cur->sub_id)
		{
			tmp = cur->sub_word;
			cur->sub_word = env_value(d, tmp);
			if (cur->sub_word == NULL)
				cur->sub_id = INV_VAR;
			free(tmp);
		}
		cur = cur->next;
	}
}

/*join subwords to words, does not change the "word id" nor free subwords*/
void	join_subwords(t_sub_list **head, t_token **node)
{
	t_sub_list	*cur;
	char		*join;

	cur = *head;
	join = NULL;
	while (cur)
	{
		if (cur->sub_word)
		{
			if (NULL == join)
				join = ft_strdup(cur->sub_word);
			else
				join = join_free(&join, true, &(cur->sub_word), false);
		}
		cur = cur->next;
	}
	if (join)
	{
		free((*node)->word);
		(*node)->word = join;
	}
	else if (WORD == (*node)->id)
		(*node)->id = INV_WORD;
}

//changes id of first word which has ID WORD to COMMAND if "found_cmd" false
bool	mark_word_cmd_arg(t_token *current, bool found_cmd)
{
	if (PIPE == current->id)
		found_cmd = false;
	else if (!found_cmd && WORD == current->id)
	{
		current->id = COMMAND;
		found_cmd = true;
	}
	else if (found_cmd && WORD == current->id)
		current->id = ARGUMENT;
	return (found_cmd);
}