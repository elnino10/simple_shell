#ifndef HEADER_FILES
#define HEADER_FILES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

/**
 * struct List_t - singly linked list
 * @num: node number field
 * @dir: directory
 * @next: points to the next node
 */
typedef struct List_t
{
	int num;
	char *dir;
	struct List_t *next;
} list_t;

/**
 *struct Info_t - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@path: string path for the current command
 *@arg: string generated from getline containing arguments
 *@argv: array of strings generated from arg
 *@fname: the program filename
 *@environ: custom modified copy of environ from LL env
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@history: the history node
 *@alias: the alias node
 *@env: linked list local copy of environ
 */
typedef struct Info_t
{
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	int cmd_buff_type;
	int readfd;
	int histcount;
	int env_changed;
	int status;
	char *path;
	char *arg;
	char **argv;
	char *fname;
	char **environ;
	char **cmd_buf;
	list_t *history;
	list_t *alias;
	list_t *env;
} info_t;

#define _INIT_                                                         \
	{                                                                  \
		0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, \
			NULL, NULL, NULL                                           \
	}

/**
 *struct built_in - contains built-in string
 *@type: the built-in command flag
 *@func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_in_table;

#define VOID(x) (void)(x)
#define MAX_SIZE 1024
#define READ_BUFFER_SZ 1024
#define WRITE_BUFFER_SZ 1024
#define BUFFER_FLUSH -1

#define HIST_FILE ".simple_shell_history"
#define MAX_HISTORY 4096

/*command chains*/
#define NORM_CMD 0
#define OR_CMD 1
#define AND_CMD 2
#define CHAIN_CMD 3

#define USE_GETLINE 0

#define LOWERCASE_CONVERTER 1
#define UNSIGNED_CONVERTER 2

extern char **environ;

void exec_fn(char *argv[]);
char *get_path(char *);

/*shell func*/
int hsh(info_t *, char **);
int get_built_in(info_t *);
void find_command(info_t *info);
void fork_command(info_t *info);

/*strings functions*/
int _strcmp(char *, char *);
int _strlen(char *);
char *_strdup(const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);

/*strings1 functions*/
char *start_str(const char *, const char *);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char **_strtok_func(char *, char *);

/*stdout print functions*/
void _puts(char *);
int _putchar(char);
int _putcharfd(char, int);
int _putsfd(char *, int);

/*stdout print1 functions*/
int print_dec(int, int);
char *dup_char(char *, int, int);
size_t print_list_dir(const list_t *);
size_t print_list_t(const list_t *);
int prt_alias(list_t *);

/*stderr print functions*/
int err_putchar(char);
void err_puts(char *);
void print_err(info_t *, char *);

/*path list*/
list_t *add_node_end(list_t **, const char *, int);
int del_node_at_index(list_t **, unsigned int);
list_t *node_prefix(list_t *, char *, char);
char **list_strings(list_t *);
size_t list_length(const list_t *);

/*path list2*/
ssize_t get_node_ind(list_t *, list_t *);

/*env functions*/
int create_env_list(info_t *);
char *my_getenv(const char *);
char *_getenv(info_t *, const char *);
char **get_env(info_t *);
int _setenv(info_t *, char *, char *);

/*env1 functions*/
int _unsetenv(info_t *, char *);

/*mem_alloc functions*/
char *_memset(char *, char, unsigned int);
void free_grid(char **);
void free_list_t(list_t **);
int free_ptr(void **);
void *__realloc(void *, unsigned int, unsigned int);

/*history_file functions*/
int renum_history(info_t *);
int build_history(info_t *, char *, int);
char *get_history(info_t *);
int rd_history(info_t *);
int wrt_history(info_t *);

/*get_info functions*/
void clr_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);
ssize_t read_buffer(info_t *, char *, size_t *);

/*shell_helper functions*/
int interactive_mode(info_t *);
int replace_str(char **, char *);
char *convert_num(long int, int, int);
int is_delimitter(char, char *);
char *path_finder(info_t *, char *, char *);

/*shell_helper2 functions*/
int _atoi(char *);
int __env(info_t *);

/*getline_func*/
ssize_t user_input(info_t *);
ssize_t input_buffer(info_t *, char **, size_t *);
int is_command(info_t *, char *);
void sigint_handler(__attribute__((unused)) int signal_num);
int getline_func(info_t *, char **, size_t *);

/*list_chain*/
void check_list_chain(info_t *, char *, size_t *, size_t, size_t);
int is_list_chain(info_t *, char *, size_t *);
/*int repl_alias(info_t *);*/
/*int repl_variable(info_t *);*/

/*cmd functions*/
int __exit(info_t *);
int __env(info_t *);
int __history(info_t *);

/*cmd functions2*/
int __cd(info_t *);
int __alias(info_t *info);
int set_alias(info_t *, char *);
int reset_alias(info_t *, char *);

#endif
