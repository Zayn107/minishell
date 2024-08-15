/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 18:42:46 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* do not use the "cat" cmd for testing, if it has no input it will stack!!*/
 
#include "../include/minishell.h"

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

// bool	prompt_user(t_data *d)
// {
// 	init_data(d);
// 	// prompt input
// 	// d->user_input = readline("MINISHELL=> ");
// 	// TEST VAR
// 	// d->user_input = ft_strdup("$ $? $HOME $HOME\"str\"txt $not_exist $6 $! '$?' str\"$HOME\"");
// 	// TEST PIPE
// 	d->user_input = ft_strdup(">out1 cat>out2 <<doc1|wc >>app1 -l");
// 	// d->user_input = ft_strdup("$< <file_in>file_\"out\" arg$HOME>>append arg$|cmd$? arg$_not_valid");
// 	// d->user_input = ft_strdup("> out1 >> app1 cmd arg < file_new arg << E");
// 	// d->user_input = ft_strdup(" >> append");
// 	// d->user_input = ft_strdup("< heredod\"$HOME\"$ cmd arg arg | new_cmd '$?'");
// 	// make some change
	
// 	// print user input
// 	printf("user_input: |%s|\n", d->user_input);
// 	trim_str(&(d->user_input), " ");
// 	if (invalid_user_input(d->user_input))
// 		return true;  // TODO: add free all to return
// 	lexer(d);
// 	// if (invalid_token(d))
// 	// 	return false; //TODO change later to return true, restart loop
// 	cmd_list_from_token(d, true);


// 	// print_tab(d->env);
// 	// print_token_list(d->list_token, true);
// 	print_cmd_list(d->list_cmd);
// 	free_list_token_and_subword(d->list_token);
// 	return (false);
// }

// ### TEST ###############################################################
bool	prompt_user(t_data *d)
{
	init_data(d);
	TEST_add_node("cmd,arg1,arg2,arg3,arg4", "file_in", "file_out", d);
	// TEST_add_node("cmd2,arg1,arg2,arg3,arg4", "file_in2", "file_out2", d);


	// WRITE PIPE BELOW


	print_cmd_list(d->list_cmd); //print each node of the cmd_list structure
	free_cmd_list(d->list_cmd);
	return (false); // run only once
}
