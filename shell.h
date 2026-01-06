#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* input.c */
char *read_line(void);
char **split_line(char *line);

/* executor.c */
int execute_cmd(char **args, char **env, char *prog_name, int line_count);

/* path.c */
char *get_path(char **env);
char *find_command(char *cmd, char **env);

/* builtins.c */
int is_builtin(char *cmd);
int handle_builtin(char **args, char **env);
int handle_exit(char **args);
int handle_env(char **env);

/* helpers.c */
void print_error(char *prog_name, int line_count, char *cmd);
void free_array(char **array);

/* string_utils.c */
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
int _strlen(char *s);

#endif
