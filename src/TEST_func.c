/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:41:06 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/18 19:28:40 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*each func call adds a node to the "t_cmd" stucture which contains the data
nodes for piping*/
void	TEST_add_node(char *path, char *cmd_arg, char *f_in, char *f_out, t_data *d)
{
	t_cmd	*node;
	const char	*TEST_DIR = "TEST/";
	char	**tab;
	int		len_tab;
	int		idx;

	node = add_node_cmd(d);
	node = d->list_cmd;
	while (node->next)
		node = node->next;
	tab = ft_split(cmd_arg, ',');
	len_tab = 0;
	while (tab[len_tab])
		len_tab++;
	free(node->cmd_arg);
	node->cmd_arg = malloc(sizeof(char*) * (len_tab + 1));
	idx = 0;
	while (tab[idx])
	{
		node->cmd_arg[idx] = ft_strdup(tab[idx]);
		free(tab[idx]);
		idx++;
	}
	free(tab);
	node->cmd_arg[idx] = NULL;
	node->cmd_path = ft_strdup(path);
	node->f_in = ft_strjoin(TEST_DIR, f_in);
	node->f_out = ft_strjoin(TEST_DIR, f_out);
	node->fd_f_in = open(node->f_in, O_CREAT | O_RDWR, 0777);
	node->fd_f_out = open(node->f_out, O_CREAT | O_RDWR, 0777);
}

/*free all nodes t_cmd struct nodes*/
void	free_cmd_list(t_cmd *head)
{
	t_cmd	*node;
	t_cmd	*tmp;
	int		idx;

	node = head;
	while (node)
	{
		idx = 0;
		while (node->cmd_arg[idx])
		{
			free(node->cmd_arg[idx]);
			node->cmd_arg[idx] = NULL;
			idx++;
		}
		free(node->cmd_arg);
		node->cmd_arg = NULL;
		free(node->cmd_path);
		free(node->f_in);
		free(node->f_out);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

/*print cmd, args file_in file_out of each node from the t_cmd structure*/
void	print_cmd_list(t_cmd *head)
{
	t_cmd	*node;
	int		idx;

	node = head;
	print_line(180, '#');
	while (node)
	{
		p_color(3,0,5, "PATH|");
		p_color(1,1,5, node->cmd_path);
		p_color(3,0,6, " CMD|");
		p_color(1,1,6, node->cmd_arg[0]);
		p_color(3,0,4, " ARG|");
		idx = 0;
		while (NULL != node->cmd_arg[++idx])
		{
			p_color(1,1,4, node->cmd_arg[idx]);
			printf(" ");
		}
		p_color(3,0,3, " FILE_IN|");
		p_color(1,1,3, node->f_in);
		p_color(3,0,2, " FILE_OUT|");
		p_color(1,1,2, node->f_out);
		printf("\n");
		print_line(180, '-');
		node = node->next;
	}
	print_line(180, '#');
}

/*helper for print function*/
void	print_line(int width, char line_char)
{
	while (width--)
		printf("%c", line_char);
	printf("\n");
}

/*weight: 0=normal 1=bold 3=italic 4=underline
color: 0=black 1=red 2=green 3=yellow 4=blue 5=magenta 6=cyan 7=white*/
void	p_color(int weight, bool background, int color, const char *str)
{
	char	style[] = "\033[0;30m";
	const char	*STOP_STYLE = "\033[0m";
	int		len;
	char	*tmp;

	style[2] = (char) (weight + 48);
	if (background)
		style[4] = '4';
	else
		style[4] = '3';
	style[5] = (char) (color + 48);
	if (str)
	{
		len = ft_strlen(str);
		if ('\n' == str[len - 1])
		{
			tmp = ft_substr(str, 0, len -1);
			printf("%s%s%s%s", style, tmp, STOP_STYLE, "\n");
			free(tmp);
		}
		else
			printf("%s%s%s", style, str, STOP_STYLE);
	}
	else
		printf("%s%s%s", style, "NULL", STOP_STYLE);
}

/*add a new node at the end of the "cmd list" */
t_cmd	*add_node_cmd(t_data *d)
{
	t_cmd	*new_node;
	t_cmd	*current;

	new_node = (t_cmd *) malloc(sizeof(t_cmd));
	new_node->builtin_fun = NULL;
	new_node->cmd_arg = (char **) malloc(sizeof(char *) * 2);
	new_node->cmd_path = NULL;
	new_node->cmd_arg[0] = NULL;
	new_node->cmd_arg[1] = NULL;
	new_node->fd_f_in = FD_NONE;
	new_node->fd_f_out = FD_NONE;
	new_node->is_tmp_file_in = false;
	new_node->f_in = NULL;
	new_node->f_out = NULL;
	// new_node->prev = NULL;
	new_node->next = NULL;
	if (d->list_cmd == NULL)
		d->list_cmd = new_node;
	else
	{
		current = d->list_cmd;
		while (current->next != NULL)
			current = current->next;
		// new_node->prev = current;
		current->next = new_node;
	}
	return (new_node);
}

/*Tales over process, anything after this func is not executed!!*/
void	execute_node_from_cmd_list(t_cmd *node)
{
	execve(node->cmd_path, node->cmd_arg, NULL);
}
