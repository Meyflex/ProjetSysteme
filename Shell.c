
#define MAX_JOBS 100

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h> // install avec sudo apt install libreadline-dev
#include <readline/history.h> // install avec sudo apt install libreadline-dev
#include <string.h>
#include "global.h"
#include "job.h"
#include "process.h"
#include "builtin.h"


#define BOLDGREEN   "\033[1m\033[31m"      /* Bold Green */
#define reset       "\033[0m"               /* white */
#define BOLDBLUE    "\033[1m\033[33m"      /* Bold Blue */

pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

/* Make sure the shell is running interactively as the foreground job
   before proceeding. */
   

void
init_shell ()
{

  /* See if we are running interactively.  */
  shell_terminal = STDIN_FILENO;
  shell_is_interactive = isatty (shell_terminal);

  if (shell_is_interactive)
    {
      /* Loop until we are in the foreground.  */
      while (tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp ()))
        kill (- shell_pgid, SIGTTIN);

      /* Ignore interactive and job-control signals.  */
      signal (SIGINT, SIG_IGN);
      signal (SIGQUIT, SIG_IGN);
      signal (SIGTSTP, SIG_IGN);
      signal (SIGTTIN, SIG_IGN);
      signal (SIGTTOU, SIG_IGN);
      signal (SIGCHLD, SIG_IGN);

      /* Put ourselves in our own process group.  */
      shell_pgid = getpid ();
      if (setpgid (shell_pgid, shell_pgid) < 0)
        {
          perror ("Couldn't put the shell in its own process group");
          exit (1);
        }

      /* Grab control of the terminal.  */
      tcsetpgrp (shell_terminal, shell_pgid);

      /* Save default terminal attributes for shell.  */
      tcgetattr (shell_terminal, &shell_tmodes);
    }
}
    

 /* Une fonction qui cree la prompt utilisateur et les fichiers dans lesquels l'utilisateur se situe  */
    
char* Createprompt()
{
  char* prompt_str=malloc(sizeof(char)*200);
  char hostname[1024];

        gethostname(hostname, 1024);
        
        
        char cwt[100];
       
        if (getcwd(cwt, sizeof(cwt)) != NULL){
             sprintf(prompt_str,"%s%s@%s%s:%s%s%s$ ",BOLDGREEN,getenv("USER"),hostname,reset,BOLDBLUE, cwt,reset);
             
        }
        else{
            perror("getcwd() error");
            
        }
        
        return prompt_str;
}

/* qui lie les commandes de l'Utilisateur elle permet de faire l'autocompletion et ainsi l'historique des commandes  */

char *read_command()
{
  char *line=NULL;
  char *line2=Createprompt();

  line=readline(line2);
  
  add_history(line);
  free(line2);
  return line;
}








/* qui permet de creer un job avec les commandes de l'utilisateur */
void shelloop(){
    int status=1;
    do{ 
      
        char* command=read_command();
        if(strcmp(command,"exit\n")==0){
            status=0;
        }
        else if (strcmp(command,"")==0 || strcmp(command," ")==0){
              continue;        
              shelloop();
        }else {
            if (strchr(command, '&')!=NULL){

                  char* token=strtok(command,"&");
                  printf("%s\n",token);
                  launch_job(NewJob(token),0);
               }else{
                  job *j=NewJob(command);
                  launch_job(j,1);
                  free_job(j);
                  
              }
        }
          
      free(command);
    }while (status);
    
    
}


/* une fonction void qui permet l'affichage de l'introduction */
void welcomeScreen(){
        printf("\n\t================================================\n");
        printf("\t                  Shell in C \n");
        printf("\t      Elmdimegh Mohamed , Hadouaj Habib\n");
        printf("\t================================================\n");
        printf("\n\n");
}
  
int main(int argc, char *argv[])
{
    welcomeScreen();
    init_shell();
    shelloop();
    return 0;
}

