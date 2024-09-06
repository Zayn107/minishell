/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/06 10:17:00 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// d->user_input = ft_strdup("echo hello | wc");
	if (invalid_user_input(d, d->user_input))
		return (true);
	add_history(d->user_input);
	lexer(d);
	if (invalid_token(d))
		return (true);
	parser(d);

	// print_cmd_list(d->list_cmd); //print cmd list ///////////////////////////
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
	errno = 0;
}

//for debugging only, NOT for submit
// bool	prompt_user(t_data *d)
// {
// 	init_data(d);
// 	d->user_input = readline("MINISHELL=> ");

// 	// TESTING /////////////////////////////////////////////////////////////////
// 	// TEST VAR
// 	// d->user_input = ft_strdup("$ $? $?txt $HOME $HOME\"str\"txt $not_exist $6txt $! '$?' str\"$HOME\" $");
// 	// d->user_input = ft_strdup("env | cat | exit");
// 	// REDIRECT
// 	// d->user_input = ft_strdup("ls -l -a >> TEST_NO/file_x"); // word missing after meta char
// 	// HEREDOC
// 	// d->user_input = ft_strdup("<< E"); // prompt for heredoc input, write file 'tmp_heredoc_'
// 	// d->user_input = ft_strdup("<<"); // prompt for heredoc input, write file 'tmp_heredoc_'
// 	// TEST PIPE
// 	// d->user_input = ft_strdup(">out1 cat>out2 <<doc1|wc >>app1 -l");
// 	// d->user_input = ft_strdup("|wc >>app1 -l"); //no word preceding pipe
// 	// d->user_input = ft_strdup("wc >>app1 -l|"); //no word after pipe
// 	// d->user_input = ft_strdup("wc >>app1 -l||end"); //no word between pipes

// 	//BUILTIN
// 	//BUILTIN_export
// 	// d->user_input = ft_strdup("export hello=var more=varr"); // is leaking
// 	// d->user_input = ft_strdup("echo hello | wc ");

// 	// d->user_input = ft_strdup("echo hello world :) > fout | cat fout"); //redirection without word
// 	// d->user_input = ft_strdup("cat | ls | wc"); //piping
// 	// d->user_input = ft_strdup("echo hello world | wc | cat > echo.txt | cat echo.txt"); //piping
// 	// d->user_input = ft_strdup("cat | echo hello"); //piping
// 	// d->user_input = ft_strdup("cat | cat | ls"); //piping
// 	// TEST INVALID INPUT
// 	// d->user_input = ft_strdup("| wc"); //missing word before pipe
// 	// d->user_input = ft_strdup("> file cat | >"); //missing word before pipe
// 	// TESTING
// 	// d->user_input = ft_strdup("'quote1'word2'quote2'word3'quote3'last"); // prompt for heredoc input, 
// 	// write file 
// 	// d->user_input = ft_strdup("word1'quote'");

// 	// d->user_input = ft_strdup("echo text |"); //missing word after pipe, prompt user
// 	// d->user_input = ft_strdup("$< <file_in>file_\"out\" arg$HOME>>append arg$|cmd$? arg$_not_valid");
// 	// d->user_input = ft_strdup("> out1 >> app1 cmd arg < file_new arg << E");
// 	// d->user_input = ft_strdup(" >> append");
// 	// d->user_input = ft_strdup("< heredod\"$HOME\"$ cmd arg arg | new_cmd '$?'");
// 	// d->user_input = ft_strdup("one_line $not_exist");
	
// 	// PRINT USER INPUT STRING /////////////////////////////////////////////////
// 	// print_user_input(d->user_input); //print user input, for debugging //////
	
// 	if (invalid_user_input(d, d->user_input))
// 		return true;  //set to false for testing
// 	add_history(d->user_input); //IS LEAKING (memory still reachable)!!!
// 	lexer(d);
// 	if (invalid_token(d))
// 		return true;  //set to false for testing
// 	parser(d, true);
// 	assign_builtin(d->list_cmd);
// 	execute(d);
	
// 	// PRINT STATEMENTS FOR DEBUGGING //////////////////////////////////////////
// 	// print_tab(d->env); //print (at start) copied environment table //////////
// 	// print_token_list(d->list_token, true); //print token list, true: subword
// 	// print_cmd_list(d->list_cmd); //print cmd list ///////////////////////////
	
// 	free_all_except_env(d);
// 	return (true);  //set to false for testing
// }
