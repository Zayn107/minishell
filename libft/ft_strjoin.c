/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:44:14 by zkepes            #+#    #+#             */
/*   Updated: 2024/07/29 19:20:31 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Allocates (with malloc(3)) and returns a new string, which is the result of
 * the concatenation of ’s1’ and ’s2’.
 * Parameters
 * s1: The prefix string.
 * s2: The suffix string.
 * Return
 * The new string. NULL if the allocation fails. */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(&str[0], s1, s1_len + 1);
	ft_strlcpy(&str[s1_len], s2, s2_len + 1);
	return (str);
}
