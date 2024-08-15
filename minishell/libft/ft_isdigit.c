/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:49:31 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 15:53:44 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Checks whether a character is a numer (0-9).
PARAMETER
arg -> 	the character to be checked, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
non zero value ->	if it is numeric
zero value ->		if it is non numeric
NOTE
Type conversation is implicit.*/

int	ft_isdigit( int arg )
{
	if (arg >= '0' && arg <= '9')
		return (2048);
	return (0);
}
