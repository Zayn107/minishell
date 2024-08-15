/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:43:55 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:29:42 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Allocates (with malloc(3)) and returns a string representing the integer
 * received as an argument. Negative numbers must be handled.
 * Parameters
 * n: the integer to convert.
 * Return
 * The string representing the integer. NULL if the allocation fails.
 * IMPLEMENTATION
 * num_len:		counts the number of digits, if n == 0 count only 1, if n < 0
 * 				add one extra for the minus signe
 * write_str:	writes to the digits as a chatcter to the string array
 * 	write_start_end	writes the beginnig of the string and the null
 * 					terminator*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int	num_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n && ++count)
		n /= 10;
	return (count);
}

static void	write_str(int digits, char *str, long int num, int minus)
{
	while (--digits >= minus && num != 0)
	{
		str[digits] = ((char)((num % 10) + 48));
		num /= 10;
	}
}

static void	write_start_end(char *str, int n, int digits)
{
	str[digits] = '\0';
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
}

char	*ft_itoa(int n)
{
	int			digits;
	int			minus;
	char		*str;
	long int	num;

	digits = 0;
	num = n;
	if (n < 0)
	{
		minus = 1;
		num *= -1;
	}
	else
		minus = 0;
	digits = num_len(n);
	if (n == 0)
		digits = 1;
	str = malloc((digits +1) * sizeof(char));
	if (!str)
		return (NULL);
	write_start_end(str, n, digits);
	write_str(digits, str, num, minus);
	return (str);
}
