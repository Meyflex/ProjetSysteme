#include "builtin.h"

#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


 
void cd(char* path)
{	
	if(path != NULL){
  if(chdir(path) != 0)
  {
    printf("Ce dossier n'existe pas\n");
  }
}else if(path == NULL){
  if(chdir(getenv("HOME")) != 0)
  {
	printf("Ce dossier n'existe pas\n");
  }
}
}

void ls(int argc, char *argv[])
{
	if (argc == 1)
	{
		_ls(".",0,0);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l);
		}
	}
	return;
}


void _ls(const char *dir,int op_a,int op_l)
{
		struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh)
	{
		if (errno = ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL)
	{
		//If hidden files are found we continue
		if (!op_a && d->d_name[0] == '.')
			continue;
		printf("%s  ", d->d_name);
		if(op_l) printf("\n");
	}
	if(!op_l)
	printf("\n");
}





char** parse_command(char *line)
{
  char **argv=NULL;
  int argc=0;
  char *token=strtok(line, " ");
  while(token!=NULL)
    {
      argv=realloc(argv, sizeof(char*)*(argc+1));
      argv[argc]=token;
      argc++;
      token=strtok(NULL, " ");
    }
  argv=realloc(argv, sizeof(char*)*(argc+1));
  argv[argc]=NULL;
  return argv;
}



void copy(char *src1,char *dest1){
    char *src = src1;
    char *dest = dest1; 
    struct stat st;
    stat(src, &st);
    char *buffer = malloc(sizeof(char) * 1024);
    int fd_src = open(src, O_RDONLY);
    int fd_dest = open(dest, O_WRONLY | O_CREAT,0644);
    int nb_read = 0;
    while((nb_read = read(fd_src, buffer, 1024)) > 0){
        write(fd_dest, buffer, nb_read);
    } 
    free(buffer);
    close(fd_src);
    close(fd_dest);
    chmod(dest,st.st_mode);
}

void copydir(char *src, char *dest){
    DIR *dir = opendir(src);
    struct dirent *dirent;
    char *src_path = malloc(sizeof(char) * 1024);
    char *dest_path = malloc(sizeof(char) * 1024);
    while((dirent = readdir(dir)) != NULL){
        if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0){
            continue;
        }
        strcpy(src_path, src);
        strcpy(dest_path, dest);
        strcat(src_path, "/");
        strcat(src_path, dirent->d_name);
        strcat(dest_path, "/");
        strcat(dest_path, dirent->d_name);
        if(dirent->d_type == DT_DIR){
            mkdir(dest_path, 0755);
            copydir(src_path, dest_path);
        }
        else{
            copy(src_path, dest_path);
        }
    }
    free(src_path);
    free(dest_path);
    closedir(dir);
}


   



