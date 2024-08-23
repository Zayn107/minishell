/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/23 17:13:38 by zkepes           ###   ########.fr       */
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
	// d->user_input = readline("MINISHELL=> ");

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

	// d->user_input = ft_strdup("echo hello world :) > fout"); //redirection without word
	d->user_input = ft_strdup("cat | ls | wc"); //piping
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
	lexer(d);
	if (invalid_token(d))
		return false;  //set to false for testing
	parser(d, true);

	// assign_builtin(d->list_cmd);
	// call_builtin(d);
	print_cmd_list(d->list_cmd); //print cmd list ///////////////////////////
	execute_cmds(d);

	// PRINT STATEMENTS FOR DEBUGGING //////////////////////////////////////////
	// print_tab(d->env); //print (at start) copied environment table //////////
	// print_token_list(d->list_token, true); //print token list, true: subword
	print_cmd_list(d->list_cmd); //print cmd list ///////////////////////////
	
	free_all_except_env(d);
	return (false);  //set to false for testing
}

void	assign_builtin(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		// if (current->cmd_arg[0] == "pwd")
		if ((0 == ft_strncmp(current->cmd_arg[0], "echo", 4)))
			current->builtin_fun = builtin_echo;
		current = current->next;
	}
}

void	call_builtin(t_data *d)
{
	t_cmd	*current;

	current = d->list_cmd;
	while (current)
	{
		if (current->builtin_fun)
			current->builtin_fun(d, current);
		current = current->next;
	}
}

void	builtin_echo(t_data *d, t_cmd *node)
{
	int	idx;

	(void) d;
	idx = 1;
	if (NULL == node->file_out && NULL == node->next)
		node->fd_out = STDOUT_FILENO;
	while (node->cmd_arg[idx])
	{
		if (idx > 1)
			write(node->fd_out, " ", 1);
		write(node->fd_out, node->cmd_arg[idx], ft_strlen(node->cmd_arg[idx]));
		idx++;
	}
	write(node->fd_out, "\n", 1);
}

void	execute_cmds(t_data *d)
{
	t_cmd	*cmd_node;
	int		status;
	cmd_node = d->list_cmd;
	while (true)
	{
		if (cmd_node->execute)
		{
			cmd_node->pid = fork();
			if (!cmd_node->pid)		// CHILD
				original_cmd(d, cmd_node);
			else					// PARENT
			{
				cmd_node->execute = false;
				if ((0 == waitpid(cmd_node->pid, &status, WNOHANG)))
				{
					printf("pid: %d\n", cmd_node->pid);
					cmd_node->sleep = true;
				}
				if (NULL != cmd_node->next)
					cmd_node = cmd_node->next;
			}
		}
		else
			if (nobody_is_sleeping(d->list_cmd))
				break;
	}
}

bool	nobody_is_sleeping(t_cmd *head)
{
	t_cmd	*cmd_node;
	int		status;
	int		wpid;

	cmd_node = head;
	while (cmd_node)
	{	
		printf("sleep %d %s pid: %d\n", cmd_node->sleep, cmd_node->cmd_arg[0], cmd_node->pid);
		if (cmd_node->sleep)
		{
			if ((wpid = waitpid(cmd_node->pid, &status, WNOHANG)))
				cmd_node->sleep = false;
			else
			{
				printf("nobody is sleeping: status: %d wpid: %d pid: %d\n", status, wpid, cmd_node->pid);
				return (false);
			}
		}
		cmd_node = cmd_node->next;
	}
	return (true);
}

// void	close_all_pipes(t_cmd *head)
// {
// 	t_cmd	*cmd_node;

// 	cmd_node = head;
// 	while (cmd_node)
// 	{

// 		cmd_node = cmd_node->next;
// 	}
// }

void	original_cmd(t_data *d, t_cmd *node)
{
	(void) d;
	if (node->prev && node->prev->sleep == true)
		printf("not sleeping before\n");
	if (node->fd_in != FD_NONE)
	{
		printf("fd_in is true, fd:%d cmd: %s \n", node->fd_in, node->cmd_arg[0]);
		dup2(node->fd_in, STDIN_FILENO);
	}
	else if (node->prev && !(node->prev->sleep))
	{
		printf("pipe in read, cmd: %s \n", node->cmd_arg[0]);
		dup2(node->pip_in[READ], STDIN_FILENO);
	}
	if (node->fd_out != FD_NONE)
	{
		printf("fd_out, fd:%d cmd: %s \n", node->fd_out, node->cmd_arg[0]);
		dup2(node->fd_out, STDOUT_FILENO);
	}
	else
	{
		printf("pipe out, cmd: %s \n", node->cmd_arg[0]);
		dup2(node->pip_out[WRITE], STDOUT_FILENO);
	}
	printf("close befor\n");
	close_all_pipes(d->list_cmd);
	printf("close after\n");
	if ((execve(node->cmd_path, node->cmd_arg, NULL) == -1))
	{
		// write(1, "error\n", 6);
		perror("execve");
	}
	exit(1); // not needed for real cmd
}

void	close_all_pipes(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		close(current->pip_in[READ]);
		close(current->pip_in[WRITE]);
		close(current->pip_out[READ]);
		close(current->pip_out[WRITE]);
		// close(current->fd_in);
		// close(current->fd_out);
		current = current->next;
	}
}










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
