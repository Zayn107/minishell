/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:12:51 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 15:57:54 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Checks whether a character is ASCII.
PARAMETER
arg -> 	the character to be checked, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
non zero value ->	if it is ASCII
zero value ->		if it is non ASCII
NOTE
Type conversation is implicit.*/

int	ft_isascii( int arg )
{
	if (arg >= 0 && arg <= 127)
		return (1);
	return (0);
}
