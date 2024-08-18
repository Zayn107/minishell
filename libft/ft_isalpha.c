/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:56:52 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 16:02:22 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Checks whether a character is an alphabet (a to z and A-Z).
PARAMETER
c -> 	the character to be checked, is passed as character e.g. 'x' then
		converted to int, then converted to character for comparison
RETURN
non zero value ->	if it is alphabetic
zero value ->		if it is non alphabetic
NOTE
Type conversation is implicit.*/

int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1024);
	else if (c >= 'a' && c <= 'z')
		return (1024);
	return (0);
}
