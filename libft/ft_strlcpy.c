/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:50:15 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 16:14:49 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Take the full size of the buffer (not just the length) and guarantee to
 * NUL-terminate the result (as long as size is larger than 0.
 * The strlcpy() function copies up to size - 1 characters from the NUL-
 * terminated string src to dst, NUL-terminating the result.
 * NOTE
 * - Size is the buffer size of dst.
 * Buffer is the total memory space alocated to the variable, string length
 * can be shorter if therer is a Null terminator before the end of the buffer.
 * - Use the 'ft_memcpy' function for copieing, not Null terminated.
 * RETURN
 * The total length of the string they tried to create (length of src).*/

#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < size)
	{
		ft_memcpy(dst, src, src_len +1);
	}
	else if (size != 0)
	{
		ft_memcpy(dst, src, size -1);
		dst[size -1] = '\0';
	}
	return (src_len);
}
