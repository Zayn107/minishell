/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:12:51 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 15:55:52 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Checks whether a character is an alphabet (a to z and A-Z) or number (0-9).
PARAMETER
arg -> 	the character to be checked, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
non zero value ->	if it is alphabetic or numeric
zero value ->		if it is non alphabetic or non numeric
NOTE
Type conversation is implicit.*/

int	ft_isalnum( int arg )
{
	if ((arg >= '0' && arg <= '9')
		|| (arg >= 'A' && arg <= 'Z')
		|| (arg >= 'a' && arg <= 'z'))
		return (8);
	return (0);
}
