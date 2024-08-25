/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/25 16:00:15 by zkepes           ###   ########.fr       */
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

bool	prompt_user(t_data *d)
{
	init_data(d);
	d->user_input = readline("MINISHELL=> ");

	// TESTING /////////////////////////////////////////////////////////////////
	// TEST VAR
	// d->user_input = ft_strdup("$ $? $?txt $HOME $HOME\"str\"txt $not_exist $6txt $! '$?' str\"$HOME\" $");
	// REDIRECT
	// d->user_input = ft_strdup("ls -l -a >> TEST_NO/file_x"); // word missing after meta char
	// HEREDOC
	// d->user_input = ft_strdup("<< E"); // prompt for heredoc input, write file 'tmp_heredoc_'
	// d->user_input = ft_strdup("<<"); // prompt for heredoc input, write file 'tmp_heredoc_'
	// TEST PIPE
	// d->user_input = ft_strdup(">out1 cat>out2 <<doc1|wc >>app1 -l");
	// d->user_input = ft_strdup("|wc >>app1 -l"); //no word preceding pipe
	// d->user_input = ft_strdup("wc >>app1 -l|"); //no word after pipe
	// d->user_input = ft_strdup("wc >>app1 -l||end"); //no word between pipes

	// d->user_input = ft_strdup("echo hello world :) > fout | cat fout"); //redirection without word
	// d->user_input = ft_strdup("cat | ls | wc"); //piping
	// d->user_input = ft_strdup("echo hello world | wc | cat > echo.txt | cat echo.txt"); //piping
	// d->user_input = ft_strdup("cat | echo hello"); //piping
	// d->user_input = ft_strdup("cat | cat | ls"); //piping
	// TEST INVALID INPUT
	// d->user_input = ft_strdup("| wc"); //missing word before pipe
	// d->user_input = ft_strdup("> file cat | >"); //missing word before pipe
	// TESTING
	// d->user_input = ft_strdup("'quote1'word2'quote2'word3'quote3'last"); // prompt for heredoc input, 
	// write file 
	// d->user_input = ft_strdup("word1'quote'");

	// d->user_input = ft_strdup("echo text |"); //missing word after pipe, prompt user
	// d->user_input = ft_strdup("$< <file_in>file_\"out\" arg$HOME>>append arg$|cmd$? arg$_not_valid");
	// d->user_input = ft_strdup("> out1 >> app1 cmd arg < file_new arg << E");
	// d->user_input = ft_strdup(" >> append");
	// d->user_input = ft_strdup("< heredod\"$HOME\"$ cmd arg arg | new_cmd '$?'");
	// d->user_input = ft_strdup("one_line $not_exist");
	
	// PRINT USER INPUT STRING /////////////////////////////////////////////////
	// print_user_input(d->user_input); //print user input, for debugging //////
	if (invalid_user_input(d, d->user_input))
		return false;  //set to false for testing
	add_history(d->user_input);
	lexer(d);
	if (invalid_token(d))
		return false;  //set to false for testing
	parser(d, true);

	// assign_builtin(d->list_cmd);
	execute_cmds(d);

	// PRINT STATEMENTS FOR DEBUGGING //////////////////////////////////////////
	// print_tab(d->env); //print (at start) copied environment table //////////
	// print_token_list(d->list_token, true); //print token list, true: subword
	print_cmd_list(d->list_cmd); //print cmd list ///////////////////////////
	
	free_all_except_env(d);
	return (false);  //set to false for testing
}

//TODO: bad file descriptor on cat cmd without arg, happened after initialising pipes with 0 in init data






// // ### TEST ###############################################################
// bool	prompt_user(t_data *d)
// {
// 	init_data(d);
// 	TEST_add_node("/usr/bin/ls", "ls,-l,-a", "file_in", "file_out", d);


// 	// WRITE PIPE BELOW


// 	print_cmd_list(d->list_cmd); //print each node of the cmd_list structure
// 	execute_node_from_cmd_list(d->list_cmd);
// 	free_cmd_list(d->list_cmd);
// 	return (false); // run only once
// }

// /*Tales over process, anything after this func is not executed!!*/
// void	execute_node_from_cmd_list(t_cmd *node)
// {
// 	execve(node->cmd_path, node->cmd_arg, NULL);
// }
