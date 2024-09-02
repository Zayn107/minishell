/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:37:11 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/02 16:45:47 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*weight: 0=normal 1=bold 3=italic 4=underline
color: 0=black 1=red 2=green 3=yellow 4=blue 5=magenta 6=cyan 7=white*/
void	p_color(int weight, bool background, int color, const char *str)
{
	char		*style;
	const char	*stop_style = "\033[0m";
	int			len;
	char		*tmp;

	style = style_str(weight, background, color);
	if (str)
	{
		len = ft_strlen(str);
		if ('\n' == str[len - 1])
		{
			tmp = ft_substr(str, 0, len -1);
			printf("%s%s%s%s", style, tmp, stop_style, "\n");
			free(tmp);
		}
		else
			printf("%s%s%s", style, str, stop_style);
	}
	else
		printf("%s%s%s", style, "NULL", stop_style);
	free(style);
}

char	*style_str(int weight, bool background, int color)
{
	char	*style;

	style = ft_strdup("\033[0;30m");
	style[2] = (char)(weight + 48);
	if (background)
		style[4] = '4';
	else
		style[4] = '3';
	style[5] = (char)(color + 48);
	return (style);
}
