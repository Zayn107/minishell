/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:58:33 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 16:44:41 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Compares the two strings s1 and s2 character by character. As soon they become
different the comparsion stops and the result is returned. The comparison is
done using unsigned characters.
PARAMETER
*s1, *s2 ->	strings to be compared
n ->		maximum length to be compared
RETURN
Compares only the first (at most) n bytes of s1 and s2.
• 0, if the s1 and s2 are equal;
• a negative value if s1 is less than s2;
• a positive value if s1 is greater than s2.
IMPLEMENTATION
-> copieing the address of the strings to a new pointer which is not a const
and a unsigned char
-> check within the loop,
	-> if string is at '\0' set _no_end to false
	-> if stings are different, return the difference in value at that point
NOTE
The locale is not taken into account. */

#include <stdio.h>
#include <stdbool.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	bool			s1_no_end;
	bool			s2_no_end;
	size_t			ind;
	unsigned char	*s1_cp;
	unsigned char	*s2_cp;

	s1_no_end = true;
	s2_no_end = true;
	ind = 0;
	s1_cp = (unsigned char *) s1;
	s2_cp = (unsigned char *) s2;
	while (ind < n
		&& s1_no_end
		&& s2_no_end)
	{
		if (s1_cp[ind] == '\0')
			s1_no_end = false;
		if (s2_cp[ind] == '\0')
			s2_no_end = false;
		if (s1_cp[ind] != s2_cp[ind])
			return ((int) s1_cp[ind] - (int) s2_cp[ind]);
		ind++;
	}
	return (0);
}
