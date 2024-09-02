/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:01:41 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 15:56:49 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	e_msg(const char *e_message)
{
	perror(e_message);
	return (false);
}

/*return: 'false' "bash: " + word + e_msg + '\n'*/
bool	bash_msg(const char *word, const char *e_msg)
{
	p_color(E_STY, E_BAC, E_COL, "bash: ");
	p_color(E_STY, E_BAC, E_COL, word);
	p_color(E_STY, E_BAC, E_COL, e_msg);
	printf("\n");
	return (false);
}

/*return: 'false' "bash: " + e_msg + word + '\n'*/
bool	bash_msg1(const char *word, const char *e_msg)
{
	p_color(E_STY, E_BAC, E_COL, "bash: ");
	p_color(E_STY, E_BAC, E_COL, e_msg);
	p_color(E_STY, E_BAC, E_COL, word);
	printf("\n");
	return (false);
}

/*return: 'false' word + e_msg + '\n'*/
bool	bash_msg2(const char *word, const char *e_msg)
{
	p_color(E_STY, E_BAC, E_COL, word);
	p_color(E_STY, E_BAC, E_COL, e_msg);
	printf("\n");
	return (false);
}

/*return: 'false' s_start (beginning) + word (middle) + s_end (end)*/
bool	bash_msg3(const char *s_start, const char *word, const char *s_end)
{
	p_color(E_STY, E_BAC, E_COL, s_start);
	p_color(E_STY, E_BAC, E_COL, word);
	p_color(E_STY, E_BAC, E_COL, s_end);
	printf("\n");
	return (false);
}
