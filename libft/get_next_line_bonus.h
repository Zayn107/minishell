/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:54:50 by zkepes            #+#    #+#             */
/*   Updated: 2023/11/20 11:16:47 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <stdbool.h>
# define STR_RETURN 1025
# define STR_SWAP 1026
# define N 1027
# define READ_ERROR -1
# define END_OF_FILE 0
# define NOT_FOUND_N -1

int		ft_malloc_set_idx(char **ptr, size_t size, bool mal);
char	*get_next_line(int fd);
char	*ft_split_read(char *array[], int fd, int idx);
char	*ft_free_null(char **ptr1, char **ptr2, char **ptr3);
void	ft_scpy(char *dst, char *src, int len);
void	ft_add_read(char *array[], int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

#endif