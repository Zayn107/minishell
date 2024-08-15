/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:41:06 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/15 18:41:44 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	TEST_add_node(char *cmd_arg, char *f_in, char *f_out, t_data *d)
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
	node->f_in = ft_strjoin(TEST_DIR, f_in);
	node->f_out = ft_strjoin(TEST_DIR, f_out);
	node->fd_f_in = open(node->f_in, O_CREAT | O_RDWR, 0777);
	node->fd_f_out = open(node->f_out, O_CREAT | O_RDWR, 0777);
}