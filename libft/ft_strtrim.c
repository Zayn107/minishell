/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:40:09 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/19 10:33:47 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description
Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
specified in ’set’ removed from the beginning and the end of the string.
Parameters
s1: 	The string to be trimmed.
set: The reference set of characters to trim.
Return
The trimmed string. NULL if the allocation fails.
IMPLEMENTATION
ft_trim_star ->	writes from original string starting from left to right
				without characters from the 'set string' to 'str_sta'
ft_trim_end ->	writes from 'str_sta' but now from the back without
				characters from the 'set string' to ' 'str_end'
*ft_strtrim ->	creates memory for 2 strings based on the original str
				which will hold the filterd string str_sta and str_end,
				create a 3th string based on the length of the 2nd string,
				copy the 2nd to the last (for correct lenght), frees the
				first two and returns the last string*/

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void	ft_trim_start( \
			char *str_sta, char const *str_ori, char const *str_set)
{
	int		ind_ori;
	int		ind_set;
	int		ind_sta;
	bool	write;

	ind_ori = 0;
	ind_set = 0;
	ind_sta = 0;
	while (str_ori[ind_ori])
	{
		write = true;
		while (str_set[ind_set] && write)
		{
			if (!ft_strncmp(&str_ori[ind_ori], &str_set[ind_set], 1))
				write = false;
			ind_set++;
		}
		if (write)
			str_sta[ind_sta++] = str_ori[ind_ori];
		if (!write)
			ind_set = 0;
		ind_ori++;
	}
	str_sta[ind_sta] = '\0';
}

static int	ft_write_to_str(char *str_sta, char const *str_ori, int ind_ori)
{
	str_sta[ind_ori] = str_ori[ind_ori];
	return (1);
}

static void	ft_trim_end(char *str_end, char const *str_sta, char const *str_set)
{
	int		ind_ori;
	int		ind_set;
	int		ind_end;
	bool	write;

	ind_ori = ft_strlen(str_sta) -1;
	ind_set = 0;
	ind_end = 0;
	while (ind_ori >= 0)
	{
		write = true;
		while (str_set[ind_set] && write)
		{
			if (!ft_strncmp(&str_sta[ind_ori], &str_set[ind_set], 1))
				write = false;
			ind_set++;
		}
		if (write)
			ind_end += ft_write_to_str(str_end, str_sta, ind_ori);
		if (!write)
			ind_set = 0;
		ind_ori--;
	}
	str_end[ind_end] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_sta;
	char	*str_end;
	char	*str_tri;
	int		s1_len;

	s1_len = ft_strlen(s1);
	str_sta = (char *) malloc(s1_len +1 * sizeof(char));
	if (!str_sta)
		return (NULL);
	str_end = (char *) malloc(s1_len +1 * sizeof(char));
	if (!str_end)
		return (NULL);
	ft_trim_start(str_sta, s1, set);
	ft_trim_end(str_end, str_sta, set);
	str_tri = (char *)malloc(ft_strlen(str_end) +1 * sizeof(char));
	if (!str_tri)
		return (NULL);
	ft_strlcpy(str_tri, str_end, ft_strlen(str_end) +1);
	free(str_sta);
	free(str_end);
	return (str_tri);
}
