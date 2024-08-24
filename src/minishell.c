/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:10 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/24 17:18:03 by zkepes           ###   ########.fr       */
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
	// d->user_input = ft_strdup("echo hello world | wc | cat > echo.txt | cat echo.txt"); //piping
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
	lexer(d);
	if (invalid_token(d))
		return false;  //set to false for testing
	parser(d, true);

	// assign_builtin(d->list_cmd);
	// call_builtin(d);
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
			current->process_child = builtin_echo;
		current = current->next;
	}
}

void	call_builtin(t_data *d)
{
	t_cmd	*current;

	current = d->list_cmd;
	while (current)
	{
		if (current->process_child)
			current->process_child(d, current);
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

	cmd_node = d->list_cmd;
	while (true)
	{
		if (cmd_node)
		{
			create_pipes(d, cmd_node);
			cmd_node->pid = fork();
			if (CHILD_PROCESS == cmd_node->pid)
				cmd_node->process_child(d, cmd_node);
			else
				cmd_node = process_parent(d, cmd_node);
		}
		else
		{
			copy_pipe_content(d->pip_out[READ], WRITE, false);
			if (nobody_is_sleeping(d->list_cmd))
				break;
		}
	}
}

void	create_pipes(t_data *d, t_cmd *cmd_node)
{
	pipe(d->pip_in);
	if (cmd_node->prev && !cmd_node->sleep)
		copy_pipe_content(d->pip_out[READ], d->pip_in[WRITE], false);
	close(d->pip_out[READ]);
	pipe(d->pip_out);
}

t_cmd	*process_parent(t_data *d, t_cmd *cmd_node)
{
	close(d->pip_in[READ]);
	close(d->pip_in[WRITE]);
	close(d->pip_out[WRITE]);
	// cmd_node->execute = false;
	if (!(cmd_node->sleep = are_you_sleeping(cmd_node->pid)))
		wait(NULL);
	else
		close(d->pip_out[READ]);
	return (cmd_node->next);
}

bool	are_you_sleeping(pid_t pid)
{
	char	*path;
	char	*str_pid;
	char	*buffer;
	int		fd;
	bool	is_sleeping;

	is_sleeping = false;
	str_pid = ft_itoa(pid);
	buffer = ft_strdup("/proc/");
	path = join_free(&buffer,  true, &str_pid, true);
	buffer = ft_strdup("/status");
	path = join_free(&path, true, &buffer, true);
	fd = open(path, O_RDONLY);
	free(path);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (ft_strnstr(buffer, "S (sleeping)", ft_strlen(buffer)))
			is_sleeping = true;
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (is_sleeping);
}

bool	nobody_is_sleeping(t_cmd *head)
{
	t_cmd	*cmd_node;

	cmd_node = head;
	while (cmd_node)
	{	
		if (cmd_node->sleep)
		{
			cmd_node->sleep = are_you_sleeping(cmd_node->pid);
			if (cmd_node->sleep)
				return (false);
		}
		cmd_node = cmd_node->next;
	}
	return (true);
}

void	original_cmd(t_data *d, t_cmd *node)
{
	close(d->pip_in[WRITE]);
	close(d->pip_out[READ]);
	if (node->fd_in != FD_NONE)
	{
		// printf("fd_in is true, fd:%d cmd: %s \n", node->fd_in, node->cmd_arg[0]);
		dup2(node->fd_in, STDIN_FILENO);
	}
	else if (node->prev && !(node->prev->sleep))
	{
		// printf("pipe in read, cmd: %s \n", node->cmd_arg[0]);
		dup2(d->pip_in[READ], STDIN_FILENO);
	}
	if (node->fd_out != FD_NONE)
	{
		// printf("fd_out, fd:%d cmd: %s \n", node->fd_out, node->cmd_arg[0]);
		dup2(node->fd_out, STDOUT_FILENO);
	}
	else
	{
		// printf("pipe out, cmd: %s \n", node->cmd_arg[0]);
		dup2(d->pip_out[WRITE], STDOUT_FILENO);
	}
	close(d->pip_in[READ]);
	close(d->pip_out[WRITE]);
	if ((execve(node->cmd_path, node->cmd_arg, NULL) == -1))
		perror("execve");
}

// void	close_all_pipes(t_cmd *head)
// {
// 	t_cmd	*current;

// 	current = head;
// 	while (current)
// 	{
// 		close(current->pip_in[READ]);
// 		close(current->pip_in[WRITE]);
// 		close(current->pip_out[READ]);
// 		close(current->pip_out[WRITE]);
// 		// close(current->fd_in);
// 		// close(current->fd_out);
// 		current = current->next;
// 	}
// }










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
