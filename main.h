#ifndef HEADER_FILES
#define HEADER_FILES
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
 
/**
 * struct List - singly linked list
 * @num: node number field
 * @dir: directory
 * @next: points to the next node
 */
typedef struct List_t {
	int num;
	char *dir;
	struct List_t *next;
} list_t;
 
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@cmd_buf_type: CMD_type ||, &&, ;
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
 
#define _INIT_ \
{0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL,\
NULL, NULL, NULL}
 
/**
 *struct built_in - contains a built-in strings
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
 
#define LOWERCASE_CONVERTER 1
#define UNSIGNED_CONVERTER 2
 
extern char **environ;
 
void exec_fn(char *argv[]);
char *get_path(char *);
 
/*shell func*/
int hsh(info_t *, char **);
int get_built_in(info_t *);
void find_command(info_t *info);
 
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
 
/*stdout print functions*/
void _puts(char *);
int _putchar(char);
int _putcharfd(char c, int fd);
int _putsfd(char *s, int fd);
 
/*path list*/
list_t *add_node_end(list_t **, const char *, int);
int del_node_at_index(list_t **, unsigned int);
list_t *node_prefix(list_t *, char *, char);
 
/*env functions*/
int create_env_list(info_t *);
char *my_getenv(const char *);
char *_getenv(info_t *, const char *);
 
/*mem_alloc functions*/
char *_memset(char *, char, unsigned int);
void free_grid(char **);
 
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
 
/*shell_helper functions*/
int interactive_mode(info_t *);
int replace_str(char **, char *);
char *convert_num(long int, int, int);
 
/*getline_func*/
ssize_t user_input(info_t *);
ssize_t input_buffer(info_t *, char **, size_t *);
 
/*list_chain*/
void check_list_chain(info_t *, char *, size_t *, size_t, size_t);
int is_list_chain(info_t *, char *, size_t *);
int repl_alias(info_t *);
int repl_variable(info_t *);
#endif
