/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:37:11 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/11 16:32:12 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	e_p_color(int weight, bool background, int color, const char *str)
{
	char		*style;
	const char	*stop_style = "\033[0m";

	style = ft_strdup("\033[0;30m");
	style[2] = (char)(weight + 48);
	if (background)
		style[4] = '4';
	else
		style[4] = '3';
	style[5] = (char)(color + 48);
	write(2, style, ft_strlen(style));
	if (str)
		write(2, str, ft_strlen(str));
	else
		write(2, "NULL", 4);
	write(2, stop_style, ft_strlen(stop_style));
	free(style);
}

void	print_doc_list(t_doc **head)
{
	t_doc	*node;

	node = *head;
	printf("print doc list:\n");
	while (node)
	{
		printf("word: %s ", node->word);
		if (node->id == WORD)
			printf("WORD");
		else if (node->id == VAR)
			printf("VAR");
		else if (node->id == VAR_EXIT)
			printf("VAR_EXIT");
		else if (node->id == INV_VAR)
			printf("INV_VAR");
		printf("\n");
		node = node->next;
	}
}
