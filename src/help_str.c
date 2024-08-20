/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:24:54 by zkepes            #+#    #+#             */
/*   Updated: 2024/08/20 18:55:10 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*cut "str" from the index to end, return new Malloc, free "str"*/
char	*cut_str(char *str, int start)
{
	char	*tmp;

	tmp = ft_strdup(&(str[start]));
	free(str);
	return (tmp);
}
