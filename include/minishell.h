#ifndef MINISHELL_H
# define MINISHELL_H

// print colors and styles
# define C_ERROR "\033[36;1m"
# define C_STOP "\033[0m"
# define BLACK 0
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define WHITE 7
# define STOP "\033[0m"
# define NORMALE 0
# define BOLD 1
# define ITALIC 3
# define UNDERLINE 4
//error message
# define E_STY 0
# define E_BAC 0
# define E_COL 1
// id for word or meta characters
# define UNPROCESSED 0
# define NO_QUOTES 1
# define QUOTE_SINGLE 2
# define QUOTE_DOUBLE 3
# define COMMAND 4
# define ARGUMENT 5
# define FILE_IN 6
# define HEREDOC 7
# define FILE_OUT 8
# define FILE_APPEND 9
# define PIPE 10
# define WORD 11
# define STRING 12
# define VAR 13
# define VAR_EXIT 14
# define INV_VAR 15
# define FD_NONE INT_MIN
// is needed for "struct sigaction"
# define _GNU_SOURCE

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>

typedef void (*ptr_builtin)(char *arg);	// definition for function pointer, builtin

typedef struct s_cmd
{
	ptr_builtin		builtin_fun;	// function pointer for builtin
	char			*cmd_path;		// MALLOC!! path + /cmd (one string)
	char			**cmd_arg;		// MALLOC!! tab[0]=cmd; tab[1]=args; tab[2]=NULL
	int				fd_f_in;		// file descriptor for direct-in files
	int				fd_f_out;		// file descriptor for direct-out files
	bool			is_tmp_file_in;	// true, remove file after use
	char			*f_in;			// MALLOC!! direct-in file name
	char			*f_out;			// MALLOC!! direct-out file name
	struct s_cmd	*prev;			// previous node in the list
	struct s_cmd	*next;			// next node in the list
}	t_cmd;

typedef struct s_data
{
	char			**env;			// MALLOC!! list of env variables
	char			*user_input;	// MALLOC!! user input string
	int				exit_status;	// replace with the last, do not reset
	struct s_cmd	*list_cmd;		// MALLOC!! list of commands
	int				pip_out[2];		// fd for pipe to be used for child output
	int				pip_in[2];		// fd for pipe to be used for child input
} t_data;

bool	prompt_user(t_data *data);

// TEST PIPE
t_cmd	*add_node_cmd(t_data *d);
void	TEST_add_node(char *path, char *cmd_arg, char *f_in, char *f_out, t_data *d);
void	execute_node_from_cmd_list(t_cmd *node);
void	print_cmd_list(t_cmd *head);
void	print_line(int width, char line_char);
void	p_color(int weight, bool background, int color, const char *str);
void	free_cmd_list(t_cmd *head);
#endif
