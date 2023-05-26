#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int exit_shell(info_t *info);
int change_directory(info_t *info);
int display_help(info_t *info);
int display_history(info_t *info);
int handle_alias_builtin(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node_to_start(list_t **head, const char *str, int num);
list_t *add_node_to_end(list_t **head, const char *str, int num);
size_t print_list_strings(const list_t *node);
ssize_t get_input(info_t *info);
int _getline(info_t *info, char**, size_t*);
void sigintHandler(int);
void clear_info(info_t *info);
void set_info(info_t *info, char**);
void free_info(info_t *info, int);
char *get_env_value(info_t *info, const char*);
int print_env_variables(info_t *info);
int set_env_variable(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *prefix);
int _setenv(info_t *info, char *var, char *value);
int delete_node_by_index(list_t **head, unsigned int index);
void free_linked_list(list_t **head_ptr);
size_t list_length(const list_t *node);
char **list_to_string_array(list_t *node);
size_t print_linked_list(const list_t *node);
list_t *find_node_with_prefix(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
int is_chain_delimiter(info_t *info, char*, size_t*);
void check_should_chain(info_t *info, char*, size_t*, size_t, size_t);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int _string_replace(char **old, char *new);
int main_shell_loop(info_t *info, char **av);
int find_builtin_command(info_t *info);
void find_command(info_t *info);
void fork_command(info_t *info);
int is_executable_command(info_t *info, char *c);
char *duplicate_chars(char *, int, int);
char *find_command_path(info_t *info, char *pathstr, char *cmd);
int loophsh(char **);
void _print_string(char *);
int _print_char(char);
int _write_to_fd(char c, int fd);
int _write_string_to_fd(char *str, int fd);
int get_string_length(char *);
int string_compare(char *, char *);
char *is_prefix(const char *, const char *);
char *string_concatenate(char *, char *);
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int print_character(char);
char *_copy_string(char *, char *, int);
char *_concatenate_strings(char *, char *, int);
char *_find_character(char *, char);
char **split_string_into_words(char *, char *);
char **split_string_into_words_2(char *, char);
char *custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);
int free_and_null_ptr(void **);
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_int(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);



#endif
