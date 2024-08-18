/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:37:31 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/19 11:10:13 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting ’s’ using the character stored in ’c’ as a delimiter.
 * The array must end with a NULL pointer.
 * Parameters
 * s: The string to be split.
 * c: The delimiter character.
 * External functs.
 * malloc, free
 * Return value
 * The array of new strings resulting from the split. NULL if the allocation
 * fails.
 * IMPLEMENTATION
 * The code is split into severel functions to make it more readable and to
 * complie with nominette formating.
 * ft_initiate_vars:    reduce max lines in code
 * *ft_free:            if memory allocation faile, then free the previouse
 *                      created memory and return a NULL pointer
 * *fill_word:          create memory based on the lenght of the word, copy
 * 						word indto memory and returns it
 * word_count:          count how many words so the first array (which holds
 *                      the array of pointers to the words) can be set to the
 *                      right size (is total size )
 * ft_split:            unites all other functions*/

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static void	ft_initiate_vars(size_t *idx_str, int *j, int *start_word)
{
	*idx_str = 0;
	*j = 0;
	*start_word = -1;
}

static void	*ft_free(char **strs, int words)
{
	int	idx;

	idx = 0;
	while (idx < words)
	{
		free(strs[idx]);
		idx++;
	}
	free(strs);
	return (NULL);
}

static char	*fill_word(const char *str, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static int	word_count(const char *str, char c)
{
	int		count;
	bool	found_str;

	count = 0;
	found_str = false;
	while (*str)
	{
		if (*str != c && !found_str)
		{
			found_str = true;
			count++;
		}
		else if (*str == c)
			found_str = false;
		str++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	idx_str;
	int		idx_row;
	int		start_word;

	ft_initiate_vars(&idx_str, &idx_row, &start_word);
	tab = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	while (idx_str <= ft_strlen(s))
	{
		if (s[idx_str] != c && start_word < 0)
			start_word = idx_str;
		else if ((s[idx_str] == c || idx_str == ft_strlen(s))
			&& start_word >= 0)
		{
			tab[idx_row] = fill_word(s, start_word, idx_str);
			if (!(tab[idx_row]))
				return (ft_free(tab, idx_row));
			start_word = -1;
			idx_row++;
		}
		idx_str++;
	}
	return (tab);
}
