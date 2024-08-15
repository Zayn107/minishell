/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:39:48 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:27:44 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Take the full size of the buffer (not just the length) and guarantee to
NUL-terminate the result (as long as size is larger than 0 or, in the case
of strlcat(), as long as there is at least one byte free in dst).
The strlcat() function appends the NUL-terminated string src to the end of
dst. It will append at most size - strlen(dst) - 1 bytes, NUL-terminating
the result.
PARAMETER
*dst ->	the string where we want to append the source to
*src ->	the string we want to append to the end of dst string
size ->	the buffer size of dst (total space of dst not just the lenght which
		is defined by the null terminator)
RETURN
Return the total length of the string they tried to create. That means the
initial length of dst plus the length of src. While this may seem somewhat
confusing, it was done to make truncation detection simple.
NOTE
If strlcat() traverses size characters without finding a NUL, the length of
the string is considered to be size and the destination string will not be
NULL-terminated.
IMPLEMENTATION
1st IF:	in case the size is 0 and one of the strings is pointing to null,
		to protect function from crushing, just return size
2nd IF:	in case there is no space in dst because size is smaller or equal,
		just return what should have been created 'size + len_dst'
3th IF:	length of the source is smaller than the difference of 'size - dst'
		copy memory from the beginning of src till including Null term.
		to dst end
ELSE:	just copy the difference of 'size - dst -1 (Null T.)' from src to
		dst and null terminate the last place*/

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;

	if ((src == NULL && size == 0) || (dst == NULL && size == 0))
		return (size);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (len_dst >= size)
		return (size + len_src);
	if (len_src < size - len_dst)
		ft_memcpy(&dst[len_dst], src, len_src + 1);
	else
	{
		ft_memcpy(&dst[len_dst], src, size - len_dst - 1);
		dst[size - 1] = '\0';
	}
	return (len_dst + len_src);
}
