/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:00:47 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:23:55 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
The calloc() function allocates a specific amount of memory and initializes it
to zero. The function can be cast to the desired type when it returns to a
void pointer to the memory location.
PARAMETER
nitems: -> how many units of memory
size:	-> size of a single unit in memory
RETURN
The function can be cast to the desired type when it returns to a
void pointer to the memory location.
IMPLEMENTATION
1. ->	to avoid overlow from the arguments and to return a "dummy"
		pointer which can be freed.
2. ->	create memory of the size ntimes * size
3. ->	set every byte in the memory to zero*/

#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nitems, size_t size)
{
	unsigned char	*str;

	if (nitems == 0 || size == 0)
	{
		str = malloc(0);
		return (str);
	}
	if ((INT_MAX / nitems) < size)
		return (NULL);
	str = (void *) malloc(nitems * size);
	if (!str)
		return (NULL);
	ft_bzero(str, nitems * size);
	return (str);
}
