/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:04:15 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 15:56:46 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Outputs the string ’s’ to the given file descriptor followed by a newline.
 * Parameters
 * s:	The string to output.
 * fd:	The file descriptor on which to write. */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	end;

	end = '\n';
	write(fd, s, ft_strlen(s));
	write(fd, &end, 1);
}
