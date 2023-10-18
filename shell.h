#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/wait.h>

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/**
 * struct liststr - singly linked list
 * @num: number
 * @str: string
 * @next: next node points
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

extern char **environ;

/**
 * struct passinfo - has fuction arguments to allow uniform prototype
 * @arg: arguments string
 * @argv: string array generated from arg
 * @sh_str_path: command string path
 * @sh_arg_cnt: number of arguments
 * @sh_line_cnt: number of errrors
 * @sh_error_code: the exit error code
 * @sh_linecnt_flag: if True, count this line of input
 * @sh_prog_filename: the program filename
 * @sh_env: linked list local copy of environ
 * @sh_environ_cpy: environ custom modified copy from LL env
 * @sh_hist_node: history node
 * @sh_alias_node: alias node
 * @sh_env_changed_flag: True if environment was changed
 * @last_cmd_status: last executed command return status
 * @cmd_buffer_address: cmd_buf pointer address, on if chaining
 * @sh_cmd_buf_type: CMD_type ||, &&, ;
 * @sh_read_filedes: read line input file descriptor
 * @sh_hist_cnt: number of history line
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *sh_str_path;
	int sh_arg_cnt;
	unsigned int sh_line_cnt;
	int sh_error_code;
	int sh_linecnt_flag;
	char *sh_prog_filename;
	list_t *sh_env;
	list_t *sh_hist_node;
	list_t *sh_alias_node;
	char **sh_environ_cpy;
	int sh_env_changed_flag;
	int last_cmd_status;
	char **cmd_buffer_address;
	int sh_cmd_buf_type;
	int sh_read_filedes;
	int sh_hist_cnt;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* _shell_atoi.c */
int _isalphabet(int);
int is_delimiter(char, char *);
int is_interactive(info_t *);
int _sh_atoi(char *);

/* _shell_built.c */
int reset_alias(info_t *, char *);
int _hist(info_t *);
int alias_print(list_t *);
int alias_set(info_t *, char *);
int _alias(info_t *);

/* _shell_builtin.c */
int sh_exit(info_t *);
int _cd(info_t *);
int _help(info_t *);

/* _shell_error.c */
int _strtoi(char *);
void rm_comments(char *);
int print_decimal(int, int);
char *cnvt_number(long int, int, int);
void error_print(info_t *, char *);

/* _shell_errors.c */
int _shellputfd(char, int);
int _shellputchar(char);
void _shell_eputs(char *);
int _shellputsfd(char *, int);

/* _shell_exit.c */
char *_shell_strch(char *, char);
char *_shell_strncat(char *, char *, int);
char *_shell_strncpy(char *, char *, int);

/* _shell_getenv.c */
char **_shell_get_environ(info_t *);
int sh_setenv(info_t *, char *, char *);
int sh_unsetenv(info_t *, char *);

/* _shell_env.c */
char *_shellgetenv(info_t *, const char *);
int sh_myenv(info_t *);
int sh_mysetenv(info_t *);
int sh_myunsetenv(info_t *);
int sh_populate_env_list(info_t *);

/* _shell_mem.c */
int bfree_ptr(void **);

/* _shell_getinfo.c */
void _shell_set_inf(info_t *, char **);
void _shell_clear_info(info_t *);
void _shell_free_inf(info_t *, int);

/* _shell_getline.c */
ssize_t _shell_input_buff(info_t *, char **, size_t *);
ssize_t shell_read_buffe(info_t *, char *, size_t *);
ssize_t shell_get_input(info_t *);
void shell_sigHandler(int);
int shell_getline(info_t *, char **, size_t *);

/* _shell_hist.c */
char *shell_get_history_file(info_t *info);
int shell_rd_history(info_t *info);
int shell_wr_history(info_t *info);
int shell_renum_history(info_t *info);
int shell_bld_hist_list(info_t *info, char *buf, int linecount);

/* _shell_list.c */
list_t *sh_add_node_end(list_t **, const char *, int);
list_t *shell_add_node(list_t **, const char *, int);
size_t print_ls_str(const list_t *);
void sh_free_list(list_t **);
int index_delete_node(list_t **, unsigned int);

/* _shell_lists.c */
char **list_to_str_array(list_t *);
size_t shell_lst_ln(const list_t *);
ssize_t _index_node(list_t *, list_t *);
list_t *node_start_pref(list_t *, char *, char);
size_t sh_ls_print(const list_t *);

/* _shell_loop.c */
int hsh_main_loop(info_t *, char **);
void sh_find_cmd_path(info_t *);
int sh_get_builtin_cmd(info_t *);
void sh_fork_exec_cmd(info_t *);

/* _shell_parse.c */
char *sh_find_path_cmd(info_t *, char *, char *);
int check_file_cmd(info_t *, char *);
char *duplicate_characters(char *, int, int);

/* _shell_realloc.c */
void ffree_str(char **);
void *sh_mem_realloc(void *, unsigned int, unsigned int);
char *_shell_memset(char *, char, unsigned int);

/* _shell_str.c */
char *sh_starts_with(const char *, const char *);
int sh_strlen(char *);
char *sh_strcat(char *, char *);
int sh_strcmp(char *, char *);

/* _shell_string.c */
int _shell_putchar(char);
char *_shell_strcpy(char *, char *);
void _shell_puts(char *);
char *_shell_strdup(const char *);


/* _shell_token.c */
char **sh_str_to_words2(char *, char);
char **sh_str_to_words(char *, char *);

/* _shell_var.c */
void sh_chain_check(info_t *, char *, size_t *, size_t, size_t);
int sh_replace_tk_alias(info_t *);
int sh_test_is_chain(info_t *, char *, size_t *);
int sh_replace_tk_vars(info_t *);
int sh_string_replace(char **, char *);

#endif
