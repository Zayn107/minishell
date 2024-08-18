/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:01:46 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 13:31:50 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Applies the function ’f’ to each character of the string ’s’, and passing
 * its index as first argument to create a new string (with malloc(3))
 * resulting from successive applications of ’f’.
 * Parameters
 * s: The string on which to iterate.
 * f: The function to apply to each character.
 * Return
 * The string created from the successive applications of ’f’. Returns NULL if
 * the allocation fails.
 * IMPLEMENTATION
 * 1. 	check the lenght of the string
 * 2. 	create enought memory for the return of function 'f' + '\0',
 * 		rerurn NULL if memory allocation fails
 * 3.	loop through the function and place resolte into new string*/

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len_s;
	int		idx;
	char	*str;

	len_s = ft_strlen(s);
	idx = 0;
	str = malloc((len_s +1) * sizeof(char));
	if (!str)
		return (NULL);
	while (idx < len_s)
	{
		str[idx] = f(idx, s[idx]);
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
