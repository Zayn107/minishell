/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:17:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 21:31:19 by zkepes           ###   ########.fr       */
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
