/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:34:10 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/14 13:43:51 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description
 * Applies the function ’f’ on each character of the string passed as argument,
 * passing its index as first argument. Each character is passed by address to
 * ’f’ to be modified if necessary.
 * Parameters
 * s: The string on which to iterate.
 * f: The function to apply to each character.*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		f(idx, &s[idx]);
		idx++;
	}
}
