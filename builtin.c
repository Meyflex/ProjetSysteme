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


void pwd(void){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("Unable to get current working directory");
}
void exit_shell(void){
    exit(EXIT_SUCCESS);
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



void copyfile(char *src, char *dest){
    struct stat info;
    char *buffer = malloc(sizeof(char) * 1024);
    int fd_src = open(src, O_RDONLY);
    int fd_dest = open(dest, O_WRONLY | O_CREAT, 0644);
    fstat(fd_src, &info);
    int nb_read = 0;
    while((nb_read = read(fd_src, buffer, 1024)) > 0){
        write(fd_dest, buffer, nb_read);
    }
    free(buffer);
    fchmod(fd_dest, info.st_mode);
    close(fd_src);
    close(fd_dest);
}
void copyF(char *src, char *dest){
    DIR *repsrc;
    DIR *repdest;
    struct stat buf;
    stat(src,&buf);
    if(S_ISDIR(buf.st_mode)) {
        repsrc= opendir(src);
        repdest=opendir(dest);
        struct dirent *dir;
        dir=readdir(repsrc);
        dir=readdir(repsrc); 
        while ((dir = readdir(repsrc)) != NULL){
            if(dir->d_type==DT_DIR) {
                char srcnew[100],destnew[100];
                strcpy(srcnew,src);
                strcat(srcnew,"/");
                strcat(srcnew,dir->d_name);
                strcpy(destnew,dest);
                strcat(destnew,"/");
                strcat(destnew,dir->d_name);
                mkdir(destnew,S_IRWXU);
                copyF(srcnew,destnew);
            }
            else if(dir->d_type==DT_REG){
                char srcnew[100],destnew[100];
                strcpy(srcnew,src);
                strcat(srcnew,"/");
                strcat(srcnew,dir->d_name);
                strcpy(destnew,dest);
                strcat(destnew,"/");
                strcat(destnew,dir->d_name);
                copyfile(srcnew,destnew);
            }else{
                printf("\nCe fichier/répertoire %s est inaccessible.\n",dir->d_name);
            }
        }
        closedir(repsrc);
        closedir(repdest);
    }
    else if(S_ISREG(buf.st_mode)){
            char *base;
            char destnew[100];
            base=basename(src);
            strcpy(destnew,dest);
            strcat(destnew,"/");
            strcat(destnew,base);
            copyfile(src,destnew);
    }else{
        printf("\nCe fichier/répertoire %s n'existe pas.\n",src);
    }

   
}


