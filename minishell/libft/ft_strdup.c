/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:07:27 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 18:20:54 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * The  strdup() function returns a pointer to a new string which is a duplicate
 * of the string s. Memory for the new string is obtained with malloc(3), and can
 * be freed with free(3).
 * RETURN
 * On  success, the strdup() function returns a pointer to the duplicated string.
 * It returns NULL if insufficient memory was available, with errno set to
 * indicate the cause of the error.*/

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*strd;

	s_len = ft_strlen(s);
	strd = (char *) malloc(s_len +1 * sizeof(char));
	if (!strd)
		return (NULL);
	ft_strlcpy(strd, s, s_len +1);
	return (strd);
}
