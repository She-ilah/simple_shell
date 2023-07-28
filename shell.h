#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

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
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
 * struct builtin - Function contains a builtin string.
 * @type: command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int main_shell(info_t *, char **);
int builtin_cmd(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void shell_puts(char *);
int shell_putchar(char);
int shell_putstwo(char c, int fd);
int shell_putstwo2(char *str, int fd);

char *starts_with(const char *, const char *);
int _strcmp(char *str_one, char *str_two);
char *_strcat(char *destinat, char *source);
int _strlen(char *str);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

int free_ptr(void **);

int shell_on(info_t *);
int char_split(char, char *);
int is_letter(int);
int convert_to_int(char *);

int str_to_int(char *);
void shell_printf_err(info_t *, char *);
int shell_printf_dec(int, int);
char *shell_con(long int, int, int);
void shell_prep(char *);

int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

int shell_history(info_t *);
int shell_alias(info_t *);

ssize_t shell_input(info_t *);
int _getline(info_t *, char **, size_t *);
void _block(int);

void init_info(info_t *);
void shell_info(info_t *, char **);
void shell_free_info(info_t *, int);

char *shell_env_val(info_t *, const char *);
int shell_env(info_t *);
int shell_set_env(info_t *);
int shell_unset_env(info_t *);
int fill_env_list(info_t *);

char **shell_ret_env(info_t *);
int shell_rev_env(info_t *, char *);
int shell_init_env(info_t *, char *, char *);

char *get_history(info_t *check);
int shell_write_hist(info_t *check);
int shell_rhist(info_t *check);
int append_history(info_t *check, char *buffer, int count);
int sort_history(info_t *check);

list_t *add_node(list_t **, const char *, int);
list_t *append_list(list_t **, const char *, int);
size_t shell_str(const list_t *);
int rm_node(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **string_list(list_t *);
size_t shell_printf_list(const list_t *);
list_t *pre_node(list_t *, char *, char);
ssize_t index_node(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void halt_chain(info_t *, char *, size_t *, size_t, size_t);
int new_alias(info_t *);
int new_vars(info_t *);
int new_string(char **, char *);

#endif

