/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:43:54 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/10 17:04:30 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*evaluate_str_var(char *str, t_data *d)
// {
// 	int		idx;
// 	char	*start;
// 	char	*start_var;

// 	idx = 0;
// 	start = str;
// 	while (str[idx])
// 	{
// 		if ('$' == str[idx] && ' ' != str[idx +1])
// 		{
// 			start_var = str[idx++];
// 			if ('_' == str[idx] || ft_isalpha(str[idx]))
// 			idx++;
// 			while ('_' == idx_var[len] || ft_isalnum(idx_var[len]))
// 				idx++;
// 		}

// 		idx++;
// 	}
// }