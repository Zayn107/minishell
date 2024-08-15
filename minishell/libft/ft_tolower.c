/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:43 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 16:08:16 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Convert uppercase letters to lowercase.
PARAMETER
c -> 	the character to be converted, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
a - z ->	if c is a uppercase character a corosponding lowercase character
			is returned, otherwise the same input character is returned
NOTE
Type conversation is implicit.*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
