/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:38:01 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/17 14:57:52 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Converts the initial portion of the string pointed to by 'str' to int.
 * RETURN
 * The converted value (or 0 on error).
 * IMPLEMENTATION
 * Jumps over ASCII formatting character (9-13) or an empty space if they apear
 * in the beginning of the string.
 * Jumps over 'one' plus or minus sign, set neg to '1' if minus to turn the num
 * negative on the end.
 * Adds a number to the int num for every character number which is offset by
 * '0' == 48 which is the differenc between the value and number */

#include <stdbool.h>

int	ft_atoi(const char *str)
{
	int		num;
	int		idx;
	bool	neg;

	num = 0;
	idx = 0;
	neg = false;
	while (((str[idx]) >= 9 && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			neg = true;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
		num = (num * 10) + (str[idx++] - '0');
	if (neg)
		return (num * -1);
	return (num);
}
