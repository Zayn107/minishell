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
# define WHITE 8
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

//Word ID
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
# define INV_WORD 16
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
#include <sys/ioctl.h>
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


typedef struct s_data t_data;
typedef struct s_cmd t_cmd;
typedef void (*ptr_process_f)(t_data *d, t_cmd *node);	// definition for function pointer, builtin

typedef struct s_cmd
{
	ptr_process_f	process_child;	// function pointer for builtin
	// cmd[0] => path + cmd, cmd[1] => arg, cmd[2] => NULL
	char			*cmd_path;		// MALLOC!! path + /cmd (one string)
	char			**cmd_arg;		// MALLOC!! tab[0]=cmd; tab[1]=args; tab[2]=NULL
	int				fd_in;
	int				fd_out;
	bool			is_tmp_file_in;	// true, remove file after use
	char			*file_in;		// MALLOC!! for debugging only
	char			*file_out;		// MALLOC!! for debugging only
	pid_t			pid;			// process id
	bool			sleep;
	struct s_cmd	*prev;			// previous node in the list
	struct s_cmd	*next;			// next node in the list
}	t_cmd;

typedef struct s_data
{
	char			**env;			// MALLOC!! list of env variables
	char			*user_input;	// MALLOC!! user input string
	int				exit_status;	// replace with the last, do not reset
	struct s_cmd	*list_cmd;		// MALLOC!! list of commands
	struct s_token	*list_token;	// MALLOC!! list of tokens
	int				pip_out[2];		// fd for pipe to be used for child output
	int				pip_in[2];		// fd for pipe to be used for child input
	// char			**tab_env_cmd_path; // MALLOC!! table with all env path variables
	struct s_env	*list_env;		// MALLOC!! list of env variables
} t_data;



bool	prompt_user(t_data *data);
void	init_data(t_data *data);

//ENV
void	copy_env(t_data *data, char *arge[]);
char	*env_value(t_data *d, char *var_name);

//LEXER
void	lexer(t_data *d);
void	prompt_if_pipe_last(t_data *d);
void	cut_user_input_into_token(t_data *d);
void	cut_quotes_subwords(t_sub_list **node, char *word);
void	cut_input_add_list_token(t_data *d, int token, int skip);
void	add_str_node_s_word(char *word, t_sub_list **node_s, int start, int len);
void	add_quo_node_s_word(char *word, t_sub_list **node_s, int start, int len);
void	cut_var_exit(t_sub_list **cur, char **tmp);
void	cut_variable_subwords(t_sub_list **head, int id_token);
void	join_subwords(t_sub_list **head, t_token **node);
void	cut_invalid_var(t_sub_list **cur, char **tmp,  char *idx_var);
void	cut_var(t_sub_list **cur, char **tmp,  char *idx_var);
void	cut_string_before_var(t_sub_list **cur, char **tmp, char *idx_var);
void	insert_node_sub_word(t_sub_list *node, int sub_id, char *sub_word);
void	add_remaining_string(t_sub_list **cur, char **tmp);
void	evaluate_variable_subwords(t_data *d, t_sub_list **head);
char	*word_after_skip(t_data *d, int token);
char	*rest_from_input(t_data *d, const char *word);
bool	mark_word_cmd_arg(t_token *current, bool found_cmd);

//PARSER
bool	parser(t_data *d, bool success);
void	assign_cmd(t_data *d, t_cmd *node, char *cmd);
char	*find_cmd_path(t_data *d, char *cmd);
void	assign_arg(char ***cmd_arg, char *new_arg);
bool	get_heredoc_input(t_cmd *n_cmd, t_token *n_token);
char	*create_heredoc_fname(bool *is_tmp_file_in);
bool	get_append(t_cmd *c_node, t_token *t_node);
bool	get_file_in(t_cmd *cur_cmd, t_token *cur_tok);
bool	get_file_out(t_cmd *c_node, t_token *t_node);
void	free_old_direction(t_cmd *node, int id);

//PRINT
void	print_user_input(char *input);
void	print_token_list(t_token *start, bool subword);
void	print_cmd_list(t_cmd *head);
void	print_line(int width, char line_char);
void	print_tab(char **tab);
void	p_color(int weight, bool background, int color, const char *str);
char	*ret_col(int weight, bool background, int color, char *str);

//FREE
void	free_tab(char **tab);
void	free_list_token_and_subword(t_token *head);
void	free_list_sub_word(t_sub_list *head);
void	free_cmd_list(t_cmd *head);
void	free_all_except_env(t_data *d);

//ERROR
void	error_exit(char *msg);
bool	bash_msg(const char *word, const char *e_msg);
bool	bash_msg1(const char *word, const char *e_msg);
bool	bash_msg2(const char *word, const char *e_msg);
bool	e_msg(const char *e_message);
bool	invalid_user_input(t_data *d, char *user_input);
bool	invalid_token(t_data *d);
char	*next_direction_character_or_new_line(t_token *current);

//STRUCTURE
void	add_node_token(t_data *d, int id, char *word);
void	add_node_sub_word(t_sub_list **node, int sub_id, char *sub_word);
t_cmd	*add_node_cmd(t_data *d);

//HELP
int		matching_quote_len(const char *str);
void	trim_str(char **str, char *cut_str);
char	*cut_str(char *str, int start);
char	*join_free(char **str1, bool free_s1, char **str2, bool free_s2);

//BUILTIN
void	builtin_echo(t_data *d, t_cmd *node);
void	assign_builtin(t_cmd *head);
void	call_builtin(t_data *d);

//TEST PIPE
void	TEST_add_node(char *path, char *cmd_arg, char *file_in, char *file_out, t_data *d);
void	execute_node_from_cmd_list(t_cmd *node);
bool	nobody_is_sleeping(t_cmd *head);

//PIPING
// void	close_all_pipes(t_cmd *head);
void	original_cmd(t_data *d, t_cmd *node);
void	execute_cmds(t_data *d);
bool	are_you_sleeping(pid_t pid);
void	copy_pipe_content(int from_fd, int to_fd, bool close_pipe);
t_cmd	*process_parent(t_data *d, t_cmd *cmd_node);
void	create_pipes(t_data *d, t_cmd *cmd_node);
void	organize_fds_according_list(t_data *d, t_cmd *node);

#endif
