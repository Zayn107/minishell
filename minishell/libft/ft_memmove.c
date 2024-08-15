/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:43:08 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:22:38 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Copies n bytes from memory area src to memory area dest. The data type dose not
matter, it can do this on any data type, because it copies byte by byte.
PARAMETERS
*dest ==>	pointer to where the bytes will be copied to
*src ==>	pointer from where the bytes are copied from
n ==>		nuber of bytes to be copied
RETURN
The pointer dest from the same position as it was passed into the function.
IMPLEMENTATION
-> the '1st if condition' checks if src and dest are not pointing to NULL or
n is 0
-> the '2nd if conditton' checks if it needs to copy from left to right or the
other way to avoid problems where the string is overlaping.
It is done by checking:
	-> if the address of the first character in dest is in the range of the
	addrress of src then copy from opy from right to left
-> loop as long the index is smaller then n, cast to a pointer of char and copy
-> by casting to a data type which is 1 byte in size, we can copy the same
data in memory even if the original data type is larger
NOTE
memmove dose the same as memcpy but it but it can also handle string overlap*/

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	if (((char *)dest == NULL && (char *)src == NULL)
		|| n == 0)
	{
		return (dest);
	}
	if (&((char *)dest)[0] < &((char *)src)[n]
		&& &((char *)dest)[0] > &((char *)src)[0])
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
	{
		while (idx < n)
		{
			((char *)dest)[idx] = ((char *)src)[idx];
			idx++;
		}
	}
	return (dest);
}
