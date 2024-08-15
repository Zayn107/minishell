/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:09:36 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 11:38:15 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tab(char **tab)
{
	while (*tab)
	{
		printf("%s\n", *tab);
		tab++;
	}
}

void	print_pipe(int fd)
{
	int		n_read;
	char	str[100];

	n_read = -1;
	printf(">>> start read:\n");
	while (n_read == -1)
	{
		n_read = read(fd, str, 100);
		// printf("n_read: %d\n", n_read);
		str[n_read] = '\0';
		printf("\t\t%s\n", str);
	}
	printf("<<< end  read:\n");

}

// for debugging
void	read_from_fd(int fd)
{
	char	buff[100];
	int 	count = 1;
	int		len;
	write(1, "/// start /// read from fd ////\n", 32);
	while (count--)
	{
		len = read(fd, buff, 100);
		write(1, buff, len);
	}
	write(1, "/// end /// read from fd ////\n", 30);
}

void	print_token_list(t_token *start, bool subword)
{
	int 		width = 180;
	t_token		*current;
	t_sub_list 	*cur_sub;

	current = start;
	while (width--)
		printf("-");
	printf("\n");
	while (current)
	{
		// print out word
		if (current->id == UNPROCESSED)
			printf("\033[0;32mUNPROCESSED\033[0m");
		else if (current->id == NO_QUOTES)
			printf("\033[0;32mNO_QUOTES\033[0m");
		else if (current->id == QUOTE_SINGLE)
			printf("\033[0;32mQUOTE_SINGLE\033[0m");
		else if (current->id == QUOTE_DOUBLE)
			printf("\033[0;32mQUOTE_DOUBLE\033[0m");
		else if (current->id == COMMAND)
			printf("\033[0;32mCOMMAND\033[0m");
		else if (current->id == ARGUMENT)
			printf("\033[0;32mARGUMENT\033[0m");
		if (current->id == FILE_IN)
			printf("\033[0;32mFILE_IN\033[0m");
		else if (current->id == HEREDOC)
			printf("\033[0;32mHEREDOC\033[0m");
		else if (current->id == FILE_OUT)
			printf("\033[0;32mFILE_OUT\033[0m");
		else if (current->id == FILE_APPEND)
			printf("\033[0;32mFILE_APPEND\033[0m");
		else if (current->id == PIPE)
			printf("\033[0;32mPIPE\033[0m");
		else if (current->id == WORD)
			printf("\033[0;32mWORD\033[0m");
		printf("|\033[1;33m%s\033[0m|", current->word);
		// print out subwords

		cur_sub = current->list_sub_word;
		while (cur_sub && subword)
		{
			if (cur_sub->sub_id == WORD)
				printf("\033[0;32m%s\033[0m|", "WORD");
			else if (cur_sub->sub_id == STRING)
				printf("\033[0;32m%s\033[0m|", "STRING");
			else if (cur_sub->sub_id == QUOTE_SINGLE)
				printf("\033[0;32m%s\033[0m|", "QUOTE_SINGLE");
			else if (cur_sub->sub_id == QUOTE_DOUBLE)
				printf("\033[0;32m%s\033[0m|", "QUOTE_DOUBLE");
			else if (cur_sub->sub_id == VAR)
				printf("\033[0;32m%s\033[0m|", "VAR");
			else if (cur_sub->sub_id == VAR_EXIT)
				printf("\033[0;32m%s\033[0m|", "VAR_EXIT");
			else if (cur_sub->sub_id == INV_VAR)
				printf("\033[0;32m%s\033[0m|", "INV_VAR");
			else if (cur_sub->sub_id == UNPROCESSED)
				printf("\033[0;32m%s\033[0m|", "UNPROCESSED");
			printf("\033[1;35m%s\033[0m|", cur_sub->sub_word);
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
	int		idx;

	node = head;
	print_line(180, '#');
	while (node)
	{
		p_color(3,0,6, "CMD|");
		p_color(1,1,6, node->cmd_arg[0]);
		p_color(3,0,4, " ARG|");
		idx = 0;
		while (NULL != node->cmd_arg[++idx])
		{
			p_color(1,1,4, node->cmd_arg[idx]);
			printf(" ");
		}
		p_color(3,0,3, " FILE_IN|");
		// if (node->file_in)
			p_color(1,1,3, node->f_in);
		// // p_color(3,0,3, " FD FILE_IN|");
		// // p_color(1,1,3, node->fd_file_in);
		p_color(3,0,2, " FILE_OUT|");
		// if (node->file_in)
			p_color(1,1,2, node->f_out);
		// // p_color(3,0,2, " FD FILE_OUT|");
		// // p_color(1,1,2, node->fd_f_out);
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

/*weight: 0=normal 1=bold 3=italic 4=underline
color: 0=black 1=red 2=green 3=yellow 4=blue 5=magenta 6=cyan 7=white*/
void	p_color(int weight, bool background, int color, const char *str)
{
	char	style[] = "\033[0;30m";
	const char	*STOP_STYLE = "\033[0m";
	int		len;
	char	*tmp;

	style[2] = (char) (weight + 48);
	if (background)
		style[4] = '4';
	else
		style[4] = '3';
	style[5] = (char) (color + 48);
	if (str)
	{
		len = ft_strlen(str);
		if ('\n' == str[len - 1])
		{
			tmp = ft_substr(str, 0, len -1);
			printf("%s%s%s%s", style, tmp, STOP_STYLE, "\n");
			free(tmp);
		}
		else
			printf("%s%s%s", style, str, STOP_STYLE);
	}
	else
		printf("%s%s%s", style, "NULL", STOP_STYLE);
}

/*returns/updates  the color code for printf as string (str), len str >= 7 and not malloc weight: 0=normal 1=bold 3=italic 4=underline
color: 0=black 1=red 2=green 3=yellow 4=blue 5=magenta 6=cyan 7=white*/
char	*ret_col(int weight, bool background, int color, char *str)
{
	char	style[] = "\033[0;30m";
	// const char	*STOP = "\033[0m";
	int			len;

	style[2] = (char) (weight + 48);
	if (background)
		style[4] = '4';
	else
		style[4] = '3';
	style[5] = (char) (color + 48);
	len = ft_strlen(style);
	printf("len: %d\n", len);
	return (ft_memcpy(str, style, len));
}
