/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:54:29 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 11:20:04 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_malloc_set_idx(char **ptr, size_t size, bool mal)
{
	size_t	idx;

	idx = 0;
	if (mal == true)
	{
		*ptr = (char *) malloc(size * sizeof(char));
		if (!ptr)
			return (0);
		while (idx < size)
			((unsigned char *)*ptr)[idx++] = '\0';
		return (1);
	}
	if (mal == false)
	{
		if (*ptr == NULL)
			return (-1);
		while ((*ptr)[idx])
		{
			if ((*ptr)[idx] == '\n')
				return (idx);
			idx++;
		}
	}
	return (-1);
}

char	*ft_free_null(char **ptr1, char **ptr2, char **ptr3)
{
	if (*ptr1 != NULL)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (*ptr2 != NULL)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	if (*ptr3 != NULL)
	{
		free(*ptr3);
		*ptr3 = NULL;
	}
	return (NULL);
}

void	ft_scpy(char *dst, char *src, int len)
{
	int	idx;

	idx = 0;
	if (len < 0)
	{
		while (src[idx])
		{
			dst[idx] = src[idx];
			idx++;
		}
	}
	else
	{
		while (idx < len)
		{
			dst[idx] = src[idx];
			idx++;
		}
	}
	dst[idx] = '\0';
}

void	ft_add_read(char *array[], int fd)
{
	int		len_fd;
	int		len_sread;
	char	*swap;

	len_fd = 0;
	if (array[fd] != NULL)
		while ((array[fd])[len_fd] != '\0')
			len_fd++;
	len_sread = 0;
	if (array[STR_SWAP] != NULL)
		while ((array[STR_SWAP])[len_sread] != '\0')
			len_sread++;
	ft_malloc_set_idx(&swap, len_fd + len_sread + 1, true);
	if (array[fd])
		ft_scpy(swap, array[fd], -1);
	ft_scpy(&(swap[len_fd]), array[STR_SWAP], -1);
	ft_free_null(&(array[fd]), &(array[N]), &(array[N]));
	ft_free_null(&(array[STR_SWAP]), &(array[N]), &(array[N]));
	array[fd] = swap;
}

char	*ft_split_read(char *array[], int fd, int idx)
{
	int		len_rest;
	char	*sreturn;
	char	*srest;

	len_rest = 0;
	if (array[fd] != NULL)
		while ((array[fd])[len_rest] != '\0')
			len_rest++;
	len_rest = len_rest - (idx + 1);
	ft_malloc_set_idx(&sreturn, idx + 2, true);
	ft_scpy(sreturn, array[fd], idx + 1);
	array[STR_RETURN] = sreturn;
	if (len_rest == 0)
		ft_free_null(&(array[fd]), &(array[N]), &(array[N]));
	else
	{
		ft_malloc_set_idx(&srest, len_rest + 1, true);
		ft_scpy(srest, &(array[fd][idx + 1]), -1);
		ft_free_null(&(array[fd]), &(array[N]), &(array[N]));
		array[fd] = srest;
	}
	return (array[STR_RETURN]);
}
