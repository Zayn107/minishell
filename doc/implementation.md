# Implementation

- [back to README "MINISHELL"](../README.md)  
---

## Overview
Data is stored in the structure `t_data data` which is often passed as just `d` to keep the lines shorter.  

1. The "original shell environment variables" are copied into the `d->env` table, from where it will be updated as long the program runs.
2. The user is prompted for input (`readline()`), which is then saved as a string and stored as first node in `list_token->word`.  
**NOTE:** even after freeing the returned malloc string from `readline()`, there is still reachable memory (`still reachable: 204,149 bytes in 221 blocks`) which can not be freed!  
3. The string is then systematically cut in it's smallest building blocks (*token*), each block is saved as a new node in the list and marked (`list_token->token`). [*see detailed explanation*](detailed_explanation.md#1-step-cut-input-into-meta-characters-and-words)  
4. Non existing files which follow `>` or `>>` are created in the current directory or **if the referenced directory exist** in there, even if the command fails, the files are still created!!  [*see detailed explanation*](./detailed_explanation.md#bash-file-creation)

---
4. The parsed user input is restructured to commands and accordantly executed.  
5. The cycle starts again with the user being prompted for input, structure freed (except err_no).  

**NOTE** :
- **Redirections** such as `<` and `<<` (*heredoc*) are handled as in-files and `>` `>>` (*append*) as out-file.
- **Pipes** `|` are handled as a new node (*command*) in the "cmd list", but if the date flows to it depends on the out-file of the last command and the in-file of the current command!
- **No space** is needed to separate redirection and pipes in the string!
- unclosed quotes `'`, `"` or "special characters" which are not required by the subject will throw an error.
- need to create directors if not existing
---
## tokenizing the user_input string
```c
typedef struct s_token
{
	int				token;			// macro to identify "token type"
	char			*word;			// part of the user input string
	struct s_token	*next;
}	t_token;
```
- The `input_user` string (`->word`) starts with the "token identifier" (`->token`) `UNPROCESSED`.
1. Check for "closed quotes" `'` or `"` and cut the string accordantly into new nodes.  
**NOTE**, "opposite quotes" which are nested within quotes lose there meaning (`"` **'** just character **'** `"`).
	- "quote checking" starts from the beginning, everything what comes after and has not yet been checked is marked `UNPROCESSED`
	- "closed quotes" are marked and cut as `QUOTE_SINGLE` or `QUOTE_DOUBLE` accordantly  
	(*the quote character is cut out from the string*)
	- everything else what has been checked is eventually marked and cut as `NO_QUOTES`
2. Every `NO_QUOTES` string is further parsed, marked and cut into: `COMMAND`, `ARGUMENT`, `FILE_IN`, `HEREDOC`, `FILE_OUT`, `FILE_APPEND`, `PIPE`.  
**Note**, that the original order of the string remains.  
