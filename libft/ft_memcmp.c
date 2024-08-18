/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:25:57 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/17 18:56:27 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
The  memcmp() function compares the first n bytes (each interpreted as
unsigned char) of the memory areas s1 and s2.
PARAMETERS
*str1, *str2 ->	strings to be copmpared
n ->			max length to be checked
RETURN
int < 0  : if str1 is smaller then str2
int > 0  : if str1 is bigger then str2
int == 0 : if str1 and str2 are equal
NOTE
All values are counted together even if there is a '\0' before the end of 'n'*/

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			idx;
	unsigned char	*cop_str1;
	unsigned char	*cop_str2;

	idx = 0;
	cop_str1 = (unsigned char *) str1;
	cop_str2 = (unsigned char *) str2;
	while (idx < n)
	{
		if (cop_str1[idx] != cop_str2[idx])
			return (cop_str1[idx] - cop_str2[idx]);
		idx++;
	}
	return (0);
}
