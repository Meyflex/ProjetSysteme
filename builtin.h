#ifndef BUILTIN_H_
#define BUILTIN_H_
#include <stdio.h>
//Used for handling directory files
#include <dirent.h>
//For EXIT codes and error handling
#include <errno.h>
#include <stdlib.h>
/* Change the current working directory */

//void cd(char** args);

/* List directory contents */
void ls(int argc, char *argv[]);
void _ls(const char *dir,int op_a,int op_l);
/* Print a helpful description of how to use the shell */
void help(void);
/* Exit the shell */
void exit_shell(void);
/* Print the current working directory */
void pwd(void);
/* Print the current process id */
char**
parse_command(char *line);

void cd(char* path);

#endif // BUILTIN_H_
