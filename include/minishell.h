#ifndef MINISHELL_H
# define MINISHELL_H

// GLOBAL VARIABLE
extern int		sig_to_children;

# define STR_PROMPT "\033[36;1mMINISHELL=>\033[0m"
# define COLOR_PROMPT "\033[36;1m"
# define C_ERROR "\033[36;1m"
# define C_STOP "\033[0m"
//colors for e_p_color
# define BLACK 0
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define WHITE 8
# define STOP "\033[0m"
//style for e_p_color
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
# define _GNU_SOURCE					// is needed for "struct sigaction"

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
#include <dirent.h>
#include <fcntl.h>						// for open()

typedef struct s_token
{
	int					id;				// use Macros to identify type
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
	bool			valid;			//is valid command?
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
	int				pip_in[2];		// fd for pipe to be used for child input
	int				pip_out[2];		// fd for pipe to be used for child output
	bool			is_pip_out;		// true if there is a pipe out
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
void	find_variable(t_sub_list *cur);

//PARSER
void	parser(t_data *d);
void	assign_cmd(t_data *d, t_cmd *node, char *cmd);
char	*find_cmd_path(t_data *d, char *cmd);
void	assign_arg(char ***cmd_arg, char *new_arg);
void	get_heredoc_input(t_cmd *c_node, t_token *t_node, char *delimiter);
char	*create_heredoc_fname(bool *is_tmp_file_in);
void	get_append(t_data *d, t_cmd *c_node, t_token *t_node);
void	get_file_in(t_data *d, t_cmd *c_node, t_token *t_node);
void	get_file_out(t_data *d, t_cmd *c_node, t_token *t_node);
void	free_old_direction(t_cmd *node, int id);
void	assign_builtin(t_cmd *node);
char	*validate_env_path(char **env_tab, char *cmd);

//BUILTIN
void	builtin_exit(t_data *d, t_cmd *node);
void	exit_program(t_data *d, t_cmd *node, int e_code, char *msg);
int		atoi_real_n(const char *str, bool *is_digit);
int		calculate_exit_status(int num);
bool	is_single_cmd(t_cmd *node);

//PRINT
void	print_user_input(char *input);
void	print_token_list(t_token *start, bool subword);
void	print_cmd_list(t_cmd *head);
void	print_line(int width, char line_char);
void	print_tab(char **tab);
void	e_p_color(int weight, bool background, int color, const char *str);

//FREE
void	free_tab(char **tab);
void	free_list_token_and_subword(t_token *head);
void	free_list_sub_word(t_sub_list *head);
void	free_cmd_list(t_cmd *head);
bool	free_all_except_env(t_data *d);

//ERROR
bool	e_fd_msg1(t_data *d, const char *word, const char *e_msg);
bool	e_vali_msg(t_data *d, const char *word, const char *e_msg);
bool	e_msg1(const char *word, const char *e_msg);
bool	e_msg2(t_data *d, const char *word, const char *e_msg);
bool	e_msg3(t_data *d, char *s_start, char *word, char *s_end);
void	e_msg(const char *e_message);
bool	invalid_user_input(t_data *d, char *user_input);
bool	invalid_token(t_data *d);
char	*next_direction_character_or_new_line(t_token *current);
void	e_bexit(t_data *d, char *msg, int error_code);

//STRUCTURE
void	add_node_token(t_data *d, int id, char *word);
void	add_node_sub_word(t_sub_list **node, int sub_id, char *sub_word);
t_cmd	*add_node_cmd(t_data *d);
void	init_new_node_cmd(t_cmd *new_node);

//HELP
int		matching_quote_len(const char *str);
void	trim_str(char **str, char *cut_str);
char	*cut_str(char *str, int start);
char	*join_free(char **str1, bool free_s1, char **str2, bool free_s2);
bool	is_digit(char *str);
// 
// void	replace_s1_with_s2(char **str1, char *str2);
void	replace_s1_with_s2(char *str1, char *str2);
void	remove_tmp_files(t_cmd *head);

//BUILTIN
void	builtin_echo(t_data *d, t_cmd *node);
void	builtin_env(t_data *d, t_cmd *node);
void	assign_builtin(t_cmd *head);
t_cmd	*process_builtin(t_data *d, t_cmd *node);
void	builtin_export(t_data *d, t_cmd *node);
char	*get_env_tab_pos(char *identifier, char **env);
bool	found_replace_var_env(char *var, char *identifier, t_data *d);
char	*get_identifier_name(char *str);
bool	identifier_is_invalid(const char *str);
void	add_var_to_env(t_data *d, char *var);
void	builtin_unset(t_data *d, t_cmd *node);
char	**remove_entry_from_env(char **env, char *entry);
void	builtin_cd(t_data *d, t_cmd *node);
void	builtin_pwd(t_data *d, t_cmd *node);
void	write_echo(char **argument, int fd, bool new_line);
void	wait_while_process_is_sleeping(t_cmd *head);

t_cmd	*skip_invalid_cmd(t_data *d, t_cmd *node, bool valid_cmd);

//PIPING
void	shell_cmd(t_data *d, t_cmd *node);
void	execute(t_data *d);
bool	are_you_sleeping(pid_t pid);
void	write_fd1_to_fd2(int fd_1, bool close_1, int fd_2, bool close_2);
t_cmd	*process_parent(t_data *d, t_cmd *cmd_node);
void	create_pipes(t_data *d, t_cmd *cmd_node);
void	dup_close_fd_child(t_data *d, t_cmd *node);

//SIGNAL
void	switch_signals(int sig_num);
// void	new_prompt(int signum);
void	new_prompt(int signum);
void	signal_all_children(t_cmd *head);

#endif
