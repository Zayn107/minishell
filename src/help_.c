/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:17:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 16:15:23 by zkepes           ###   ########.fr       */
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

void	replace_s1_with_s2(char **str1, char *str2)
{
	free(*str1);
	*str1 = ft_strdup(str2);
}
