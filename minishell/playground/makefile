EXE		=	add_history chdir dir fstat getcwd getenv rl_on_new_line \
			rl_replace_line stat unlink init_env open_dir substr execev
FLAG	=	-Werror -Wextra -Wall
LIB		= -L./../libft -lft

all: $(EXE) $(EXE)*c

%: %.c
	@$(CC) $(FLAG) $< -o $@ $(LIB) -lreadline -lhistory

clean:
	rm $(EXE)
