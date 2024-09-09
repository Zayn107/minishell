/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:17:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 17:03:05 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_tmp_files(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		if (current->is_tmp_file_in)
		{
			if (unlink(current->file_in))
				perror("unlink() error");
			current->is_tmp_file_in = false;
		}
		current = current->next;
	}
}

void	replace_s1_with_s2(char *str1, char *str2)
{
	(void) str2;

	printf("inside replace: |%s|\n", str1);
	// char	*tmp;

	// tmp = str1;
	str1 = ft_strdup(str2);
	// free(tmp);
	printf("inside replace: |%s|\n", str1);
}
