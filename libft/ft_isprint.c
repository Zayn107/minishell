/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:12:51 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 15:59:25 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Checks whether a character is an printable (ASCII 32 - 126).
PARAMETER
arg -> 	the character to be checked, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
non zero value ->	if it is printable
zero value ->		if it is non printable
NOTE
Type conversation is implicit.*/

int	ft_isprint( int arg )
{
	if (arg >= 32 && arg <= 126)
		return (16384);
	return (0);
}
