/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:43 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 16:08:25 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Convert lowercase letters to uppercase.
PARAMETER
c -> 	the character to be converted, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
A - Z ->	if c is a lowercase character a corosponding uppercase character
			is returned, otherwise the same input character is returned
NOTE
Type conversation is implicit.*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
