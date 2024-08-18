NAME = libft.a
SOURCE = \
ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset ft_bzero \
ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr \
ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin \
ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd \
ft_putnbr_fd \
get_next_line get_next_line_bonus get_next_line_utils get_next_line_utils_bonus
LIBARY = -L. -lft
CC = gcc
FLAG = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(SOURCE:=.o) libft.h get_next_line.h
	@ar rcs $(NAME) $(SOURCE:=.o)

%.o: %.c
	@$(CC) -c  $(FLAG) $< -o $@

# remove "object files"
clean:
	@rm -f $(SOURCE:=.o)

# remove "object files" and  "library"
fclean: clean
	@rm -f $(NAME)

# remove "object files", "library" and rebuild
re: fclean all

.PHONY: all clean fclean re
