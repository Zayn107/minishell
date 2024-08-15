/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:13:55 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/17 16:22:17 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description
Outputs the integer ’n’ to the given file descriptor.
Parameters
n:	The integer to output.
fd:	The file descriptor on which to write.
IMPLEMENTATION
Because we can only print single digits (ASCII offset 48), we need to break the
number down into single digits with the help of recursion.
1.	Create a bigger data type so that when 'n' has the max negative value and
	needs to be flipt dose not overflow (-2,147,483,648 to 2,147,483,647 32-bit)
2.	1st If: value is negative, write minus, make value positive by multiplying
	with -1
3.	2nd If: the number divided by 10 is not 0 (more than one digit), keep
	recalling the function till it is (recursion)
4.	Once the nuber has only one digit the first case of the recursion makes
	it through the conditon and is printed as character
see link for explanition
https://docs.google.com/drawings/d/
1kpzkfhoyMWoPsZvH1gJxDcn0EXueKekylBtJcVqBep4/edit?usp=sharing*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	if (nbr / 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + 48, fd);
}
