#include "builtin.h"

#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


//  void cd(char** args)
// {
// 	if (args[0] && args[1])
// 		{
// 		printf("shell: cd: too many arguments\n");
// 		return;
// 		}

// 	char* dir = args[0];
// 	printf("dir: %s", dir);
		
// 	if (!dir) dir = "";
			
// 	struct passwd* pw = getpwuid(getuid());
// 		char* homedir = pw->pw_dir;
		
// 	if (dir[0] == 0 || (dir[0] == '~' && dir[1] == 0)) dir = homedir;
// 	int res = chdir("dir");

// 	if (res < 0)
// 	printf("shell: cd: %s: No such directory\n", dir);
//  }


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






