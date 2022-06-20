#ifndef BUILTIN_H_
#define BUILTIN_H_
//Used for handling directory files
//For EXIT codes and error handling
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <libgen.h>



/* fonction qui permet de lister les fichiers dans le shell */
void ls(int argc, char *argv[]);
void _ls(const char *dir,int op_a,int op_l);
/* Print a helpful description of how to use the shell */
void help(void);
/* Exit the shell */
void exit_shell(void);


char**
parse_command(char *line);
/* fonction cd qui permet de changer de fichier dans le shell  */
void cd(char* path);
/* fonction qui permet de copier un fichier ou un directory dans un autre */

void copydir(char *src, char *dest);

#endif // BUILTIN_H_
