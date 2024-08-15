NAME			= minishell
# HEADER
HEADER			= include/minishell.h
# SOURCE
SRC_DIR			= src/
SRC				= $(addprefix $(SRC_DIR), \
				minishell.c print.c free.c error.c env.c \
				lexer_.c \
				lexer_cut_quotes_subwords.c \
				lexer_cut_user_input.c \
				lexer_cut_variable_subwords.c \
				struct.c \
				parser.c)
# OBJECTS
OBJ_DIR			= obj/
OBJ				= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
# LIBRARY
LIB				= -L./libft -lft
LIB_READ		= -lreadline -lhistory
ARC				= libft/libft.a
# COMPILE
CC				= cc
FLAGS			= -Werror -Wextra -Wall -g

all: $(NAME)

$(NAME): $(SRC) $(OBJ_DIR) $(OBJ) $(HEADER) $(ARC)
	$(CC) $(FLAGS) $(OBJ_DIR)*.o -o $(NAME) $(LIB) $(LIB_READ)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c $(HEADER)
	@$(CC) -c $(FLAGS) $< -o $@

$(ARC):
	@make -s -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make -s clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make -s fclean -C libft

re: fclean $(NAME)

norm:
	clear && norminette main src

.PHONY: all clean fclean re norm

# YOU NEED to compile with the "-lreadline" flag which needs to be last!!
# e.g. cc readline.c -o main -lreadline
