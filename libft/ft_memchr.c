/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:04:22 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 17:52:02 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* WHAT IS IT DOING:
 * searches for the first occurrence of the character c (an unsigned char)
 * in the first n bytes of the string pointed to, by the argument str.
 * str	− This is the pointer to the block of memory where the search is
 * 		performed.
 * c 	− This is the value to be passed as an int, but the function performs a
 * 		byte per byte search using the unsigned char conversion of this value.
 * n	− This is the number of bytes to be analyzed.
 * RETURN:
 * This function returns a pointer to the matching byte or NULL if the character
 * does not occur in the given memory area.
 * NOTE:
 * Is working the same as 'strchr' but it does not stop at '\0'.*/

#include <stdio.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if (((unsigned char *const)str)[index] == (unsigned char) c)
			return ((void *) &((unsigned char *const)str)[index]);
		index++;
	}
	return (NULL);
}
