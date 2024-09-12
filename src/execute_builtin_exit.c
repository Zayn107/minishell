/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:22:47 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/12 16:11:27 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_exit(t_data *d, t_cmd *node)
{
	int		num;
	bool	is_digit;

	if (node->cmd_arg[1])
	{
		num = atoi_real_n(node->cmd_arg[1], &is_digit);
		if (is_digit && NULL == node->cmd_arg[2])
		{
			num = calculate_exit_status(num);
			exit_program(d, node, num, NULL);
		}
		else if (is_digit && NULL != node->cmd_arg[2])
		{
			write(1, "exit\n", 5);
			e_msg2(d, "bash: exit : ", "too many arguments");
			close(d->pip_in[READ]);
			close(d->pip_out[WRITE]);
		}
		else
			exit_program(d, node, 2, "numeric argument required");
	}
	else
		exit_program(d, node, 0, NULL);
}

void	exit_program(t_data *d, t_cmd *node, int e_code, char *msg)
{
	write(1, "exit\n", 5);
	if (msg)
	{
		e_p_color(E_STY, E_BAC, E_COL, "bash: exit: ");
		e_p_color(E_STY, E_BAC, E_COL, msg);
		write(2, "\n", 1);
	}
	if (!is_single_cmd(node))
	{
		close(d->pip_in[READ]);
		close(d->pip_out[WRITE]);
		return ;
	}
	free_all_except_env(d);
	free_tab(d->env);
	exit(e_code);
}

int	atoi_real_n(const char *str, bool *is_digit)
{
	int		num;
	int		idx;
	bool	neg;

	num = 0;
	idx = 0;
	neg = false;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			neg = true;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
		num = (num * 10) + (str[idx++] - '0');
	if (idx != (int)ft_strlen(str))
		*is_digit = false;
	else
		*is_digit = true;
	if (neg)
		return (num * -1);
	return (num);
}

int	calculate_exit_status(int num)
{
	int	count_zeros;
	int	rest;

	if (0 == num)
		return (0);
	if (0 < num)
	{
		count_zeros = num / 255;
		rest = num % 255;
		return (rest - count_zeros);
	}
	else
	{
		num *= -1;
		count_zeros = num / 255;
		num -= count_zeros;
		rest = num % 255;
		return (256 - rest);
	}
}
