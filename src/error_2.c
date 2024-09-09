/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:41:11 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 21:32:28 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*return: 'false' "bash: " + e_msg + word + '\n'*/
bool	e_vali_msg(t_data *d, const char *word, const char *e_msg)
{
	e_p_color(E_STY, E_BAC, E_COL, "bash: ");
	e_p_color(E_STY, E_BAC, E_COL, e_msg);
	e_p_color(E_STY, E_BAC, E_COL, word);
	write(2, "\n", 1);
	d->exit_status = 2;
	return (false);
}

void	e_bexit(t_data *d, char *msg, int error_code)
{
	e_p_color(E_STY, E_BAC, E_COL, "bash: exit: ");
	e_p_color(E_STY, E_BAC, E_COL, msg);
	write(2, "\n", 1);
	d->exit_status = error_code;
}

void	e_msg_and_exit(char *cmd, char *e_msg, int e_code)
{
	e_msg1(cmd, e_msg);
	exit(e_code);
}

void	exit_if_directory_or_not_cmd(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (NULL != dir)
	{
		closedir(dir);
		e_msg_and_exit(cmd, ": Is a directory", 126);
	}
	else
	{
		closedir(dir);
		e_msg_and_exit(cmd, ": command not found", 127);
	}
}
