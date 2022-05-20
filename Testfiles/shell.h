#ifndef _SIMPLESHELL_H_
#define _SIMPLESHELL_H_
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#define N_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a" /*needs work */

/*buitins*/
int func_exit(char **args);
void func_printenv(char **env);

/*main.c*/
char *read_input(void);
char **toparse_str(char *line, char **env);
int execute(char **args, char **argv, int count, char *line, char **env);
void prompt(void);
void handle_signal(int signal);

/*error and stat*/
int *_error(char *argv, int count, char *args);
int _stat(char **cmd, char **path);

/*which*/
char **_which(char *foundpath);
char *_getenv(char *name, char **env);
char *search_func(char **dir, char *cmd);
int child_process(char **av, char **args, char **environ, int st, int countt);
int _access(char *filename);

/*STRINGS*/
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *_strstr(char *str1, char *str2);
char *_strdup(char *str);
char *_itoa(int num, int base);

void *_realloc(void *ptr, unsigned int new_size);
int _count_point(char *buffer);

/*others*/
void *_calloc(unsigned int nmemb, unsigned int size);
char *str_concat(char *s1, char *s2);
char **search_path(char **environ);
void _puts(char *str);
int _putchar(char c);

#endif
