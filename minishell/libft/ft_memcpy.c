/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:20 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:26:27 by zkepes           ###   ########.fr       */
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
-> the if condition checks if src and dest are not pointing to NULL or n is 0
-> loop as long the index is smaller then n, cast to a pointer of char and copy
-> by casting to a data type which is 1 byte in size, we can copy the same
data in memory even if the original data type is larger
NOTE
The memory areas must not overlap. Use memmove() for overlap.*/

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	if (((char *)dest == NULL && (char *)src == NULL)
		|| n == 0)
	{
		return (dest);
	}
	while (idx < n)
	{
		((char *)dest)[idx] = ((char *)src)[idx];
		idx++;
	}
	return (dest);
}
