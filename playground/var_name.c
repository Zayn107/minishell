/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:59:30 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/09 13:13:11 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

int	main(void)
{
	char var[] = "var_somename=value=something";
	char *varname;

	varname = ft_substr(var, 0, ft_strchr(var, '=') - &var[0]);

	printf("%s\n", varname);
	free(varname);
}