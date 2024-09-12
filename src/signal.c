/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:16:32 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/12 14:27:16 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	new_prompt(int signum)
void	new_prompt(int sig_num)
{
	(void) sig_num;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_children(int sig_num)
{
	(void) sig_num;
	g_sig_to_children = sig_num;
	if (SIGINT == sig_num)
		write(1, "\n", 1);
}

void	switch_signals(int sig_mum)
{
	if (1 == sig_mum)
	{
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (2 == sig_mum)
	{
		signal(SIGINT, signal_children);
		signal(SIGQUIT, signal_children);
	}
}

void	signal_all_children(t_cmd *head)
{
	t_cmd	*node;

	node = head;
	if (g_sig_to_children)
	{
		while (node)
		{
			kill(node->pid, g_sig_to_children);
			node->sleep = false;
			node = node->next;
		}
	}
	g_sig_to_children = 0;
}
