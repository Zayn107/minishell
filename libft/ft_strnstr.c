/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:22:12 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:25:46 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Locates the first occurrence of the null-terminated string 'sub' in the
string 'str', where not more than len characters are searched. Characters
that appear after a ‘\0’ character are not searched.
RETURN
If 'sub' is an empty string, 'str' is returned; if 'sub' occurs nowhere
in * 'str', NULL is returned; otherwise a pointer to the first character
of the first occurrence of 'sub' is returned.
IMPLEMENTATION
1st IF:	protect the function if one of the strings is NULL and lenght is 0
l49 IF:	if lenght 'str' is shorter then 'len' overwrite 'len' with 'str'
		length
l52 IF:	if 'sub' is empty, return 'str'
l54:	as long the indes is lower then length and as long index +
		length of sub is lower or equal to the length
l56:	use string n compare which advances by the index und compares
		only the length of 'sub'
l57:	if found gets the value '0' (sring is equal) return the
		position in str */

#include <string.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	idx;
	size_t	len_str;
	size_t	len_sub;
	int		found;

	if ((str == NULL && len == 0) || (sub == NULL && len == 0))
		return (NULL);
	len_str = ft_strlen(str);
	len_sub = ft_strlen(sub);
	if (len_str < len)
		len = len_str;
	idx = 0;
	if (sub[0] == '\0')
		return ((char *) str);
	while (idx < len && idx + len_sub <= len)
	{
		found = ft_strncmp(&str[idx], sub, len_sub);
		if (!found)
			return ((char *)&str[idx]);
		idx++;
	}
	return (NULL);
}
