/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:53:54 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/19 11:20:11 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
->	Linux systems limit the number of file descriptors that any one process
	may	open to 1024 per process. (0 - 1023)
*/

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			idx;
	int			read_status;
	static char	*array[1028] = {NULL};

	idx = ft_malloc_set_idx(&array[fd], 0, false);
	while (idx == NOT_FOUND_N)
	{
		ft_malloc_set_idx(&array[STR_SWAP], BUFFER_SIZE + 1, true);
		read_status = read(fd, array[STR_SWAP], BUFFER_SIZE);
		if (read_status <= READ_ERROR)
			return (ft_free_null(&(array[fd]), &(array[N]),
					&(array[STR_SWAP])));
		if (read_status == END_OF_FILE && (array[fd] == NULL))
			return (ft_free_null(&(array[STR_SWAP]), &(array[N]), &(array[N])));
		if (read_status == END_OF_FILE && (array[fd] != NULL))
		{
			array[STR_RETURN] = array[fd];
			array[fd] = NULL;
			ft_free_null(&(array[STR_SWAP]), &(array[N]), &(array[N]));
			return (array[STR_RETURN]);
		}
		ft_add_read(array, fd);
		idx = ft_malloc_set_idx(&array[fd], 0, false);
	}
	return (ft_split_read(array, fd, idx));
}
