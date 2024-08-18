/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:01:35 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/15 14:45:05 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Fills the first n bytes of the memory area pointed to by s with the character
stored in c. Even c is an int, it gets casted to an unsigned char.
PARAMETERS
s	==> is a pointer to the block of memory to fill.
c	==> is the value to be set as a character or single digit if used for
	numbers. The value is passed as an int, but the function fills the block
	of memory using the unsigned char conversion of this value.
n	==> is the number of bytes to be set to the value.
RETURN
Returns the pointer s from its 'passed in' position.
IMPLEMENTATION
Loop for the total lenght of bytes, and assignes the unsigned character to each
byte. Because byte is copied by byte, it dose not mater what size or type the
original data type is
NOTE
It is possible to set an array of integers to a one digit value. It must be one
digit becoause there is a ASCII character for it.

/// example with int array ///////////////////////////////////////////////////
    int n = 10;
    int arr[n];

    // Fill whole array with 0.
    memset(arr, 0, n*sizeof(arr[0]));

/// example with str array ///////////////////////////////////////////////////
    char str[50] = "GeeksForGeeks is for programming geeks.";

    // Fill 8 characters starting from str[13] with '.'
    memset(str + 13, '.', 8*sizeof(char));
	// before: "GeeksForGeeks is for programming geeks."
	// after:  "GeeksForGeeks........programming geeks."*/

#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
		((unsigned char *)s)[idx++] = (unsigned char) c;
	return (s);
}
