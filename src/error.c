/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:01:41 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/03 16:10:32 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	e_msg(const char *e_message)
{
	perror(e_message);
	return (false);
}

/*return: 'false' "bash: " + word + e_msg + '\n'*/
bool	e_msg1(t_data *d, const char *word, const char *e_msg)
{
	e_p_color(E_STY, E_BAC, E_COL, "bash: ");
	e_p_color(E_STY, E_BAC, E_COL, word);
	e_p_color(E_STY, E_BAC, E_COL, e_msg);
	printf("\n");
	d->exit_status = 1;
	return (false);
}


/*return: 'false' word + e_msg + '\n'*/
bool	e_msg2(t_data *d, const char *word, const char *e_msg)
{
	e_p_color(E_STY, E_BAC, E_COL, word);
	e_p_color(E_STY, E_BAC, E_COL, e_msg);
	printf("\n");
	d->exit_status = 1;
	return (false);
}

/*return: 'false' s_start (beginning) + word (middle) + s_end (end)*/
bool	e_msg3(t_data *d, char *s_start, char *word, char *s_end)
{
	e_p_color(E_STY, E_BAC, E_COL, s_start);
	e_p_color(E_STY, E_BAC, E_COL, word);
	e_p_color(E_STY, E_BAC, E_COL, s_end);
	printf("\n");
	d->exit_status = 1;
	return (false);
}

/*return: 'false' "bash: " + e_msg + word + '\n'*/
bool	e_vali_msg(t_data *d, const char *word, const char *e_msg)
{
	e_p_color(E_STY, E_BAC, E_COL, "bash: ");
	e_p_color(E_STY, E_BAC, E_COL, e_msg);
	e_p_color(E_STY, E_BAC, E_COL, word);
	printf("\n");
	d->exit_status = 2;
	return (false);
}

void	e_bexit(t_data *d, char *msg, int error_code)
{
	e_p_color(E_STY, E_BAC, E_COL, "bash: exit: ");
	e_p_color(E_STY, E_BAC, E_COL, msg);
	printf("\n");
	d->exit_status = error_code;
}