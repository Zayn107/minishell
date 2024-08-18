/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/18 19:26:50 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* do not use the "cat" cmd for testing, if it has no input it will stack!!*/
 
#include "../include/minishell.h"

int	main(void)
{
	// data structure to contain all date, to be passed as a pointer
	t_data	data;
	data.list_cmd = NULL;

	// loop which keeps the user prompting for input
	while (prompt_user(&data))
		;
}

/*place functions for processing input and piping commands in here*/
bool	prompt_user(t_data *d)
{
	TEST_add_node("/usr/bin/ls", "ls,-l,-a", "file_in", "file_out", d);


	// WRITE PIPE BELOW


	print_cmd_list(d->list_cmd); //print each node of the cmd_list structure
	execute_node_from_cmd_list(d->list_cmd);
	free_cmd_list(d->list_cmd);
	return (false); // false: run only once, true: infinite loop
}
