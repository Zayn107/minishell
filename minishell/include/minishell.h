#ifndef MINISHELL_H
# define MINISHELL_H

# define STR_PROMPT "<MINISHELL>"
# define COLOR_PROMPT "\033[36;1m"
# define C_ERROR "\033[36;1m"
# define C_STOP "\033[0m"
//colors for p_color
# define BLACK 0
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define WHITE 7
# define STOP "\033[0m"
//style for p_color
# define NORMALE 0
# define BOLD 1
# define ITALIC 3
# define UNDERLINE 4
//message
//error message
# define E_STY 0
# define E_BAC 0
# define E_COL 1


# define UNPROCESSED 0

# define NO_QUOTES 1
# define QUOTE_SINGLE 2
# define QUOTE_DOUBLE 3

# define COMMAND 4
# define ARGUMENT 5
# define FILE_IN 6
# define HEREDOC 7					//use ; to mark heredoc file
# define FILE_OUT 8
# define FILE_APPEND 9
# define PIPE 10
# define WORD 11
# define STRING 12
# define VAR 13
# define VAR_EXIT 14
# define INV_VAR 15
# define FD_NONE INT_MIN

# define DELIMITER " <>|\0"
# define META_CHAR "<>|"

# define CHILD_PROCESS 0
# define READ 0
# define WRITE 1
# define _GNU_SOURCE				// is needed for "struct sigaction"

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
#include <fcntl.h>			// for open()

typedef struct s_token
{
	int					id;			// use Macros to identify type
	char				*word;			// token data
	struct s_sub_list	*list_sub_word;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_sub_list
{
	int					sub_id;
	char				*sub_word;
	struct s_sub_list	*prev;
	struct s_sub_list	*next;
}	t_sub_list;

typedef void (*ptr_builtin)(char *arg);	// definition for function pointer, builtin

typedef struct s_cmd
{
	ptr_builtin		builtin_fun;	// function pointer for builtin
	// cmd[0] => path + cmd, cmd[1] => arg, cmd[2] => NULL
	//char			*cmd_path;		// MALLOC!! path + /cmd (one string)
	char			**cmd_arg;		// MALLOC!! tab[0]=cmd; tab[1]=args; tab[2]=NULL
	int				fd_f_in;
	int				fd_f_out;
	bool			is_tmp_file_in;	// true, remove file after use
	char			*f_in;		// for debugging only
	char			*f_out;		// for debugging only
	//char			*out_file;		// name of "last" output file (create prev) (handle append)

	// if out_file is NULL, pass stream to next cmd, otherwise no
	//char			*in_file;		// name of "last" input file (heredoc)
	// if in_file is NULL, take stream from previous cmd, otherwise from file
	struct s_cmd	*next;			// next node in the list
}	t_cmd;

typedef struct s_data
{
	char			**env;			// MALLOC!! list of env variables
	char			*user_input;	// MALLOC!! user input string
	int				exit_status;	// replace with the last, do not reset
	struct s_cmd	*list_cmd;		// MALLOC!! list of commands
	struct s_token	*list_token;	// MALLOC!! list of tokens

	int				n_cmd;			// number of commands
	int				pip_out[2];		// fd for pipe to be used for child output
	int				pip_in[2];		// fd for pipe to be used for child input
	// char			**tab_env_cmd_path; // MALLOC!! table with all env path variables
	struct s_env	*list_env;		// MALLOC!! list of env variables
	bool			last_cmd;	
} t_data;

bool	prompt_user(t_data *data);
void	init_data(t_data *data);
void	copy_env(t_data *data, char *arge[]);

// env
char	*env_value(t_data *d, char *var_name);
void	print_tab(char **tab);
void	print_pipe(int fd);
void	print_token_list(t_token *start, bool subword);
void	free_tab(char **tab);
void	free_list_token_and_subword(t_token *head);
void	free_list_sub_word(t_sub_list *head);
// error
void	error_exit(char *msg);
// testing
void	read_from_fd(int fd);
void	lexer(t_data *d);

// structure
void	add_node_token(t_data *d, int id, char *word);
void	insert_node_token_struct(t_token *current, int token, char *word);

// refactor tokenize V2
void	cut_word(t_token *current);
int		match_quote_idx(const char *str);
void	add_node_sub_word(t_sub_list **node, int sub_id, char *sub_word);
bool	invalid_user_input(char *user_input);
void	cut_user_input(t_data *d);
void	trim_str(char **str, char *cut_str);
void	cut_quotes_subwords(t_sub_list **node, char *word);
void	add_str_node_s_word(char *word, t_sub_list **node_s, int start, int len);
void	add_quo_node_s_word(char *word, t_sub_list **node_s, int start, int len);
void	cut_variable_subwords(t_sub_list **head);
void	insert_node_sub_word(t_sub_list *node, int sub_id, char *sub_word);
t_sub_list	*cut_var_exit(t_sub_list *cur, char **tmp, char *idx_var);
t_sub_list	*cut_var(t_sub_list *cur, char **tmp,  char *idx_var);
void	cut_invalid_var(char **tmp,  char *idx_var);
void	add_remaining_string(t_sub_list **cur, char **tmp);
void	evaluate_variable_subwords(t_data *d, t_sub_list **head);
void	join_subwords(t_sub_list **head, char **word);
void	insert_before_node_sub_word(t_sub_list *node, int sub_id, char *sub_word);
bool	mark_word_cmd_arg(t_token *current, bool found_cmd);
// char	*rest_from_input(t_data *d, int rest_start);
void	cut_input_add_list(t_data *d, int token, int skip);
char	*rest_from_input(t_data *d, int id, const char *word);
char	*word_from_input(t_data *d, int token);
void	create_direct_out_files_if_not_exist(t_data *d);
bool	invalid_token(t_data *d);
char	*next_meta_character_or_new_line(t_token *current);
void	free_all_except_env(t_data *d);
void	p_color(int weight, bool background, int color, const char *str);
char	*ret_col(int weight, bool background, int color, char *str);
bool	create_file_if_not_exist(t_token *head);
t_cmd	*add_node_cmd(t_data *d);
bool	cmd_list_from_token(t_data *d, bool success);
void	assign_arg(char ***cmd_arg, char *new_arg);
void	print_line(int width, char line_char);
void	print_cmd_list(t_cmd *head);
bool	get_file_in(t_cmd *cur_cmd, t_token *cur_tok);
bool	get_heredoc_input(t_cmd *n_cmd, t_token *n_token);
void	print_fd(int fd);
void	free_old_direction(t_cmd *node, int id);
char	*create_heredoc_fname(bool *is_tmp_file_in);
bool	e_msg(const char *e_message);
bool	bash_msg(const char *word, const char *e_msg);
bool	bash_msg1(const char *word, const char *e_msg);
bool	get_append(t_cmd *c_node, t_token *t_node);
bool	get_file_out(t_cmd *c_node, t_token *t_node);
t_sub_list	*cut_string_before_var(t_sub_list *cur, char **tmp, char *idx_var);
// void	p_color();
#endif
