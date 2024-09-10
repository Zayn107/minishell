/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 09:37:10 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// GLOBAL VARIABLE
int		g_sig_to_children;

int	main(const int argc, char *argv[], char *arge[])
{
	t_data	data;

	(void) argc;
	(void) argv;
	copy_env(&data, arge);
	while (prompt_user(&data))
		;
	free_tab(data.env);
}

bool	prompt_user(t_data *d)
{
	init_data(d);
	d->user_input = readline(STR_PROMPT);
	switch_signals(2);
	if (invalid_user_input(d, d->user_input))
		return (true);
	add_history(d->user_input);
	lexer(d);
	if (invalid_token(d))
		return (true);
	parser(d);
	assign_builtin(d->list_cmd);
	execute(d);
	free_all_except_env(d);
	return (true);
}

void	init_data(t_data *d)
{
	d->user_input = NULL;
	d->list_token = NULL;
	d->list_cmd = NULL;
	d->is_pip_out = false;
	g_sig_to_children = 0;
	switch_signals(1);
	errno = 0;
}

// 	// PRINT STATEMENTS FOR DEBUGGING //////////////////////////////////////////
// 	// print_tab(d->env); //print (at start)  // print env table ///////////////
// 	// print_token_list(d->list_token, true); // print token list, true: subword
// 	// print_cmd_list(d->list_cmd);           //print cmd list /////////////////
