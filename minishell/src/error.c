/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:01:41 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/14 20:26:32 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(char *msg)
{
	//TODO: implement free all
	perror(msg);
	exit(EXIT_FAILURE);
}

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
