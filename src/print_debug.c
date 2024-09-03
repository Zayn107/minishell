/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:51:37 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/03 09:33:35 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_user_input(char *input)
{
	int	width = 180;
	const char *TITLE = "= user input ==";

	e_p_color(3, false, 8, TITLE);
	e_p_color(0,true,1, input);
	while (width-- - ft_strlen(TITLE) - ft_strlen(input))
		e_p_color(0, false, 8, "=");
	printf("\n");
}

void	print_tab(char **tab)
{
	while (*tab)
	{
		printf("%s\n", *tab);
		tab++;
	}
}

void	print_token_list(t_token *start, bool subword)
{
	int 		width = 180;
	const char *TITLE = "- TOKEN list ";
	const char *TITLE_EXTENT = "with SUB WORDS ";
	int 		len_title;
	t_token		*current;
	t_sub_list 	*cur_sub;

	current = start;
	e_p_color(3,false,8, TITLE);
	len_title = ft_strlen(TITLE);
	if (subword)
	{
		e_p_color(3,false,8, TITLE_EXTENT);
		len_title += ft_strlen(TITLE_EXTENT);
	}
	while (width-- - len_title)
		printf("-");
	printf("\n");
	while (current)
	{
		// print out word
		if (current->id == UNPROCESSED)
			printf("\033[4;32mUNPROCESSED\033[0m");
		else if (current->id == NO_QUOTES)
			printf("\033[4;32mNO_QUOTES\033[0m");
		else if (current->id == QUOTE_SINGLE)
			printf("\033[4;32mQUOTE_SINGLE\033[0m");
		else if (current->id == QUOTE_DOUBLE)
			printf("\033[4;32mQUOTE_DOUBLE\033[0m");
		else if (current->id == COMMAND)
			printf("\033[4;32mCOMMAND\033[0m");
		else if (current->id == ARGUMENT)
			printf("\033[4;32mARGUMENT\033[0m");
		if (current->id == FILE_IN)
			printf("\033[4;32mFILE_IN\033[0m");
		else if (current->id == HEREDOC)
			printf("\033[4;32mHEREDOC\033[0m");
		else if (current->id == FILE_OUT)
			printf("\033[4;32mFILE_OUT\033[0m");
		else if (current->id == FILE_APPEND)
			printf("\033[4;32mFILE_APPEND\033[0m");
		else if (current->id == PIPE)
			printf("\033[4;32mPIPE\033[0m");
		else if (current->id == WORD)
			printf("\033[4;32mWORD\033[0m");
		else if (current->id == INV_WORD)
			printf("\033[4;32mINV_WORD\033[0m");
		printf("|\033[1;43m%s\033[0m|", current->word);
		// print out subwords

		cur_sub = current->list_sub_word;
		while (cur_sub && subword)
		{
			if (cur_sub->sub_id == WORD)
				printf("\033[3;32m%s\033[0m|", "WORD");
			else if (cur_sub->sub_id == STRING)
				printf("\033[3;32m%s\033[0m|", "STRING");
			else if (cur_sub->sub_id == QUOTE_SINGLE)
				printf("\033[3;32m%s\033[0m|", "QUOTE_SINGLE");
			else if (cur_sub->sub_id == QUOTE_DOUBLE)
				printf("\033[3;32m%s\033[0m|", "QUOTE_DOUBLE");
			else if (cur_sub->sub_id == VAR)
				printf("\033[3;32m%s\033[0m|", "VAR");
			else if (cur_sub->sub_id == VAR_EXIT)
				printf("\033[3;32m%s\033[0m|", "VAR_EXIT");
			else if (cur_sub->sub_id == INV_VAR)
				printf("\033[3;32m%s\033[0m|", "INV_VAR");
			else if (cur_sub->sub_id == UNPROCESSED)
				printf("\033[3;32m%s\033[0m|", "UNPROCESSED");
			printf("\033[1;45m%s\033[0m|", cur_sub->sub_word);
			cur_sub = cur_sub->next;
		}
		printf("   ");
		current = current->next;
	}
	printf("\n");
	width = 180;
	while (width--)
	printf("-");
	printf("\n");
}

void	print_cmd_list(t_cmd *head)
{
	t_cmd	*node;
	const char *TITLE = "# COMMAND list ";
	int		idx;

	node = head;
	e_p_color(3,false,8, TITLE);
	print_line(180 - ft_strlen(TITLE), '#');
	while (node)
	{
		e_p_color(3,0,5, "PATH|");
		e_p_color(1,1,5, node->cmd_path);
		e_p_color(3,0,6, " CMD|");
		e_p_color(1,1,6, node->cmd_arg[0]);
		e_p_color(3,0,4, " ARG|");
		idx = 0;
		while (NULL != node->cmd_arg[++idx])
		{
			e_p_color(1,1,4, node->cmd_arg[idx]);
			printf(" ");
		}
		e_p_color(3,0,3, " FILE_IN|");
		e_p_color(1,1,3, node->file_in);
		e_p_color(3,0,2, " FILE_OUT|");
		e_p_color(1,1,2, node->file_out);
		printf("\n");
		print_line(180, '-');
		node = node->next;
	}
	print_line(180, '#');
}

void	print_line(int width, char line_char)
{
	while (width--)
		printf("%c", line_char);
	printf("\n");
}
