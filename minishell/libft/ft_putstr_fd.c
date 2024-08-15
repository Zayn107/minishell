/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:51:03 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 14:03:10 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Outputs the string ’s’ to the given file descriptor.
 * Parameters
 * s s: The string to output.
 * fd: The file descriptor on which to write.
 * IMPLEMENTATION
 * Use the 'write' function, 2nd arg is address to pointer which contains the
 * string, last arg is the total lenght to be writen == lenght of the string.*/

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
