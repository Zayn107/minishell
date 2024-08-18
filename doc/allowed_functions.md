# Allowed Functions
- [back to README "MINISHELL"](../README.md)  
---
For the full list of allowed functions see the [subject](minishell.pdf).
## readline (functions)
The GNU Readline Library contains functions which take user input from the command line.  
Include the following headers:  
`#include <readline/readline.h` and/or `#include <readline/history.h>`.  
And link the "static library" `-lreadline -lhistory` **at the end** when compiling the executable program. [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/readline.html).
|prototype|description|
|---|---|
|`char *readline(const char *prompt);`|Prompt the user for input which needs to be terminated with **ENTER**. Note that the finale newline is removed. A "malloc pointer" of the entered string is returned but the entered string is also saved in the global variable `rl_line_buffer`.<br>[see playground readline.c](../playground/readline.c)|
|`int add_history(const char *line)`<br>-> `line`: A pointer to a null-terminated string that represents the line of text to be added to the history.<br>**Return Value**<br>-> **The function returns 0** if the line is successfully added to the history.<br>-> **It returns a non-zero** value if the operation fails. For example, failure can occur if the provided line is NULL or empty.|Is used to keep a record of the commands or input lines entered by the user. This historical record can be utilized to recall previous inputs, making it easier for users to re-execute commands or edit them.<br>[see playground add_histor.c](../playground/add_history.c)|
|`void rl_clear_history(void)`|Clears the history of entered strings (commands).<br>[see playground rl_clear_history.c](../playground/rl_clear_history.c)|
|`void rl_replace_line(const char *text, int clear_undo)`<br>-> `*text`: A pointer to a null-terminated string containing the new line of text to replace the current line buffer.<br>-> `clear_undo`: An integer that determines whether to clear the undo list. If non-zero, the undo list is cleared. If zero, the undo list is preserved.|Replaces the value of the global variable `rl_line_buffer` which was set after getting the user input with `readline()` with a new string (*text*).<br>[see playground rl_replace_line.c](../playground/rl_replace_line.c)|
|`void rl_on_new_line (void)`|When implementing an interactive command-line application and you need to ensure that the **cursor is positioned at the start** of a new line. E.g. in interactive mode, the user is entering information but you are also printing status information.<br>**!!! In practice I could not see any difference with or without the function!!!**<br>[see playground rl_on_new_line.c](../playground/rl_on_new_line.c)|
|`void rl_redisplay(void)`|Forces the Readline library to re-render the "current line buffer" on the screen.<br>**!!Had no effect in my playground!!**<br>[playground rl_replace_line.c](../playground/rl_replace_line.c)<br>Should be useful in the following scenarios:<br>-> **Programmatically Modifying the Input Line**: When you change the contents of the line buffer using functions like `rl_replace_line` or by directly manipulating `rl_line_buffer`.<br>-> **Handling Asynchronous Events**: When your program needs to update the prompt or input line in response to asynchronous events such as receiving data from a network socket.<br>-> **Custom Prompt Display**: If you change the prompt dynamically and need to ensure it is immediately updated.|

---
## getcwd (get current working directory)
Include the header: `unistd.`
|prototype|description|
|---|---|
|`char *getcwd(char *buf, size_t size)`<br>`*buf`: A pointer to an array where the pathname of the current working directory will be stored. Needs to be large enough to hold the string of the path including the null terminator.<br>`size`: The size of the array pointed to by buf.<br>**Return Value**<br>-> **On success**, it returns a pointer to the buffer buf containing the pathname of the current working directory.<br>-> **On failure**, it returns `NULL`, and `errno` is set to indicate the error.|Is used to get the current working directory of the process.<br>[see playground getcwd.c](../playground/getcwd.c)|

---
## chdir (change current working directory)
Include the header: `unistd.h`
|prototype|description|
|---|---|
|`int chdir(const char *path)`<br>`*path`: A pointer to a string containing the path to the directory you want to change to. This can be an absolute or relative path.<br>**Return Value**<br>-> **On success**, it returns `0`.<br>-> **On failure**, it returns `-1`, and `errno` is set to indicate the error.|Is used to change the current working directory of the calling process.<br>[see playground chdir.c](../playground/chdir.c)|

---
## stat (functions, file statistic)
Include the header: `sys/stat.h`
|prototype|description|
|---|---|
|`int stat(const char *path, struct stat *buf)`<br>`*path`: A pointer to a string containing the pathname of the file to be examined.<br>`struct stat *buf`: A pointer to a `struct stat` structure where the file information will be stored.<br>**Return Value**<br>**On success**, it returns `0`.<br>**On failure**, it returns `-1`, and `errno` is set to indicate the error.|Is used to retrieve information about a file. It provides detailed information about the file, such as its size, permissions, and timestamps.<br>[see playground stat.c](../playground/stat.c)|
|`int lstat(const char *path, struct stat *buf`<br>*the same as `stat` above*|Is used to retrieve information about a file, similar to the `stat` function, but with a key difference: `lstat` does not follow symbolic links. Instead, if the file specified by the pathname is a symbolic link, `lstat` returns information about the link itself.|
|`int fstat(int fd, struct stat *buf)`<br>`fd`: The file descriptor of the file for which information is to be obtained.<br>`struct stat *buf`: A pointer to a struct stat structure where the file information will be stored.<br>**Return Value**<br>**On success**, it returns `0`.<br>**On failure**, it returns `-1`, and `errno` is set to indicate the error.|Is used to retrieve detailed information about an open file using its file descriptor.<br>[see playground fstat.c](../playground/fstat.c)|

---
## unlink (remove linke / file)
Include the header: `unistd.h`
|prototype|description|
|---|---|
|`int unlink(const char *pathname)`<br>`*pathname`: A pointer to a string containing the pathname of the file to be removed.<br>**Return Value**<br>**On success**, it returns `0`.<br>**On failure**, it returns `-1`, and `errno` is set to indicate the error.|-> The unlink function removes a link to a file. If this is the last link to the file and no process has the file open, **the file is deleted** and the space it was using is freed.<br>-> If there are other links to the file, the file itself is not deleted until all links are removed and no processes have the file open.<br>[see playground unlink.c](../playground/unlink.c)|

---
## dir (directory functions)
Include the header: `dirent.h`
|prototype|description|
|---|---|
|`DIR *opendir(const char *name)`<br>***name**: A pointer to a string containing the name of the directory to be opened.<br>**Return Value**<br>-> **On success**, it returns a pointer to the DIR structure.<br>-> **On failure**, it returns NULL, and errno is set to indicate the error.|To open a directory stream corresponding to the directory name provided. This function returns a pointer to a DIR structure that can be used to read (`readdir`) the directory entries.<br>[see playground dir.c](../playground/dir.c)|
|`struct dirent *readdir(DIR *dirp)`<br>***dirp**: A pointer to the directory stream, which was opened by the `opendir` function.<br>**Return Value**<br>**On success**, it returns a pointer to a `struct dirent` structure representing the next directory entry.<br>On reaching the end of the directory stream, or if an error occurs, it returns `NULL`.|To read a directory entry from an open directory stream. This function returns a pointer to a `struct dirent` structure representing the next directory entry (*file*) in the directory stream.<br>[see playground dir.c](../playground/dir.c)|
|`int closedir(DIR *dirp)`<br>***dirp**: A pointer to the directory stream to be closed. This should be the pointer returned by a previous call to `opendir`.<br>**Return Value**<br>**On success**, it returns `0`.<br>**On failure**, it returns `-1`, and `errno` is set to indicate the error. E.g. `EBADF`: The directory stream is not valid.|The `closedir` function in C is used to close a directory stream previously opened by `opendir`. Closing the directory stream frees the resources associated with it.<br>[see playground dir.c](../playground/dir.c)|

### opendir
#### Error Handling 
If opendir fails, it returns NULL and sets errno to indicate the error. Common errors include:  
|Error|description|
|---|---|
|`EACCES`|Permission is denied to open the directory.|
|`EMFILE`|The per-process limit on the number of open file descriptors has been reached.|
|`ENFILE`|The system-wide limit on the total number of open files has been reached.|
|`ENOENT`|The directory does not exist.|
|`ENOTDIR`|The name is not a directory.|

#### Practical Considerations 
- **Directory Stream:** The directory stream opened by `opendir` must be closed using `closedir` to release resources.
- **Reading Entries:** Use `readdir` to read entries from the directory stream. This function returns a pointer to a struct dirent, which contains information about each directory entry.
- **Thread Safety:** The `opendir` function is thread-safe, but the DIR structure it returns is not. Each thread should have its own DIR structure if they need to read the same directory concurrently.

### readdir
#### struct dirent Structure
The struct dirent structure represents a directory entry. Here are some of the key fields:
|field|description|
|---|---|
|`ino_t d_ino`|Inode number.|
|`off_t d_off`|Offset to the next dirent.|
|`unsigned short d_reclen`|Length of this record.|
|`unsigned char d_type`|Type of the file (not supported by all file systems).|
|`char d_name[]`|Null-terminated filename.|

#### Error Handling
If `readdir` returns `NULL`, you need to check whether it is due to reaching the end of the directory or an error. You can use the `errno` variable to check for errors:  
`EBADF`: The directory stream is not valid.

#### Practical Considerations
- **End of Directory**: When `readdir` returns `NULL`, it can mean either the end of the directory has been reached or an error occurred. You should check `errno` to differentiate between these cases.
- **Thread Safety**: The `readdir` function itself is thread-safe, but concurrent calls to `readdir` on the same directory stream from multiple threads can result in undefined behavior. Each thread should have its own `DIR` structure if they need to read the same directory concurrently.
- **d_type Field**: The `d_type` field in the `struct dirent` structure provides information about the type of the file (e.g., regular file, directory). However, this field is not supported by all filesystems and should not be solely relied upon.

### closedir
#### Practical Considerations
- **Resource Management**: It is important to call closedir to free the resources associated with the directory stream after you are done using it.
- **Multiple closedir Calls**: Calling closedir more than once on the same DIR pointer results in undefined behavior. Ensure each directory stream is closed only once.
- **Error Checking**: Always check the return value of closedir to ensure it has succeeded.

---
## getenv (get env variables)
|field|description|
|---|---|
|`char *getenv(const char *name)`<br>***name**: A pointer to a `null-terminated` string containing the name of the environment variable whose value you want to retrieve.<br>**Return Value**<br>**On success**, it returns a pointer to the `null-terminated` string containing the value of the environment variable.<br>If the environment variable **does not exist**, it returns `NULL`.|Is used to retrieve the value of an environment variable. Environment variables are key-value pairs maintained by the operating system to pass information about the operating environment to processes.<br>[see playground getenv.c](../playground/getenv.c)|

### Error Handling
- If the specified environment variable is not found, `getenv` returns `NULL`. It is essential to check for `NULL` to handle cases where the environment variable does not exist.
- `getenv` does not set `errno`.

### Practical Considerations

- **Thread Safety**: `getenv` is generally not thread-safe. Modifying environment variables or calling `getenv` from multiple threads without proper synchronization can lead to undefined behavior.
- **Security**: Be cautious when using environment variables, especially in security-sensitive applications. Environment variables can be modified by users or processes, potentially leading to security risks if their values are used without validation.
- **Memory Management**: The pointer returned by `getenv` points to a string in the environment list. Do not attempt to modify this string or free the memory.