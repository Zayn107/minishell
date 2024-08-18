/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:48:50 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:21:33 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Allocates (with malloc(3)) and returns a substring from the string ’s’. The
 * substring begins at index ’start’ and is of maximum size ’len’.
 * Parameters
 * s: 		The string from which to create the substring.
 * start: 	The start index of the substring in the string ’s’.
 * len:		The maximum length of the substring.
 * Return:
 * The substring. NULL if the allocation fails.
 * NOTE:
 * The first part is to check the input parameter are within range.
 * */
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str_sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		str_sub = (char *) malloc(1);
		str_sub[0] = '\0';
		return (str_sub);
	}
	if (len > s_len)
		len = s_len;
	if (len > s_len - start && s_len - start > 0)
		len = s_len - start;
	str_sub = (char *) malloc(len +1 * sizeof(char));
	if (!str_sub)
		return (NULL);
	ft_strlcpy(str_sub, &s[start], len +1);
	return (str_sub);
}
