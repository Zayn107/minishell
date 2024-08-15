# Detailed Explanation

- [back to README "MINISHELL"](../README.md)  
---

## Cut user input into token
- [back to "IMPLEMENTATION"](./implementation.md#overview)  

The user input is saved as first node in the list `d.list_token.word` and marked under *token* as `UNPROCESSED`.  

```c
typedef struct s_token
{
	int					token;			// macro to identify token type
	char				*word;			// user input string
	struct s_sub_list	*list_sub_word;
	struct s_token		*next;
}	t_token;
```  
The string is systematically cut into token, each token becomes one node in the list and is cut off from the "*unprocessed*" string. The remaining "*unprocessed*" sting is added to the end as a new node, the process repeats until the entire string is tokenized.  

### 1. step: cut input into "*meta characters*" and "*words*"  
- white space is trimmed from the beginning and the end of the unprocessed string
- if the first character is `<`, `>` or `|` then it is a "meta character" otherwise it is a "word" until whitespace or a "meta character" follows.
- **Meta characters** are `<` `<<` `>>` `>` `|`.  
- **Words** consist of all the characters which are not "meta characters" or white space.  

|character in string|`int` `d.list_token.token`  (*macro*)|`char*` `d.list_token.word`|
|---|---|---|
|`<`|`FILE_IN`|`NULL`|
|`<<`|`HEREDOC`|`NULL`|
|`>>`|`FILE_APPEND`|`NULL`|
|`>`|`FILE_OUT`|`NULL`|
|`\|`|`PIPE`|`NULL`|
|*anything else apart form whitespace*|`WORD`|*original string*|  

### 2. step: cut "**words**" into "**sub words**"  (*words, quotes and variables*)

```c
typedef struct s_sub_list
{
	int					token;		// macro to identify token type
	char				*sub_word;	// sub-words and variables
	struct s_sub_list	*next;
}	t_sub_list;
```  

- Each node has a list of "**sub word**"s, which is used to cut the string further down into quotes and variables `$`.  
- First we cut into quotes, variables and/or strings.
- If "double quotes" are found then it may need to be cut further if it contain's variables.  

|characters in string|`int` `d.list_token.token`  (*macro*)|`char*` `d.list_token.word`|
|---|---|---|
|Starting and ending with `'`.| `QUOTE_SINGLE`|Containing the string from withing the quotes.|
|Starting and ending with `"`.| `QUOTE_DOUBLE`|Containing the string from withing the quotes.|
|Any sequence of characters (not space or meta characters) which is not quoted.| `WORD`|Unmodified string.|  

**NOTE:** "Matching outer quotes" are removed but "opposite quotes" (*e.g.* `"`->`'` *or* `'`->`"`) and  "meta characters" within remain, they are treated as regular characters!  


|`int` `d.list_token.list_sub_word.token` (*macro*)|description|
|---|---|
|`VAR_EXIT`|`$?` Second character after `$` is a `?` then it is always the "exit status variable", the rest before or after is treated as string or other variable.|
|`VAR`|**valid variable names:**<br/>-> 1st character after `$` **MUST BE** alphabetic or underscore,<br/>-> 2nd character after `$` alphanumeric or underscore, otherwise the variable name ends.<br/>**invalid variable names:**<br/>-> are removed from the string, *e.g.* `text$42after_txt` *becomes->* `text2after_txt`<br/><br/>**NOTE:** The subject stats clearly that only the following characters `<`, `<<`,`>>`, `>`, `\|`, `""`, `''`, `$` `$?` have special meaning! The "bash" has "special variables" which are not part of the project's scope!|

### 3. step: replace valid variable names  
- The "**exit variable**" is replaced with value of the variable `d.exit_status`.
- If the name of the variable is found in the table of `d.env` then it is replaced with its value (*e.g.* `VAR_NAME=VAR_VALUE`), otherwise the `sub_word` gets the value `NULL` (*removed from string*).

### 4. step: put sub words back together  
- Join all "sub words" (`d.list_token.list_sub_word.token`) and replace "word" `d.list_token.word`.

---
## Bash file creation
### When are files created?
- After `>` or `>>`, only the first file name is used, even if the command(s) are invalid.  
*e.g.* `xxx echo > file1 file2 > file3` *output->* `command 'xxx' not found` but the files `file1` and `file3` are created if they not already exist.
### What if the directory dose not exist?
- All files which can be created are created regardless, the shell throws an error and waits for new user input. `bash: `...`: No such file or directory`
