/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:01:35 by zkepes            #+#    #+#             */
/*   Updated: 2023/10/31 17:53:44 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Fills the first n bytes of the memory area pointed to by s with the
Null Terminator ('\0') which is '0' on an number data type.
PARAMETER
s ==>	beginning of the string address of memeroy to be filled
n ==>	number of bytes to be filled
NOTE
The bzero() function is deprecated, use memset(3) instead.*/

#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
		((char *)s)[idx++] = '\0';
}
