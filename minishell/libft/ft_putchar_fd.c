/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:41:08 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 13:50:12 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Outputs the character ’c’ to the given file descriptor.
 * Parameters
 * c:	The character to output.
 * fd:	The file descriptor on which to write.*/

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
