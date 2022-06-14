
#define MAX_JOBS 100

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


#include <string.h>
#include "global.h"
#include "job.h"
#include "process.h"
#include "builtin.h"
#define BOLDGREEN   "\033[1m\033[31m"      /* Bold Green */
#define reset  "\033[0m"
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
    

//read command from shell function using getline

char *read_command()
{
  char *line=NULL;
  ssize_t line_size;
  getline(&line, &line_size, stdin);
  line[strlen(line)-1]=0;
 // line[line_size-2]=0;

  return line;
}


void shelloop(){
    int status=1;
    do{ 
        char hostname[1024];
        gethostname(hostname, 1024);
        printf(BOLDGREEN"%s@%s",getenv("USER"),hostname);
        printf(reset":");
        char cwt[100];
        if (getcwd(cwt, sizeof(cwt)) != NULL){
            printf(BOLDBLUE "%s", cwt);
            printf(reset"$ "); 
        }
        else{
            perror("getcwd() error");
        }
        
        char* help=read_command();
        if(strcmp(help,"exit\n")==0){
            status=0;
        }
        else if (strcmp(help,"")==0){
              continue;        
              shelloop();
            }else{
               if (strchr(help, '&')!=NULL){

                  char* token=strtok(help,"&");
                  printf("%s\n",token);
                  launch_job(NewJob(token),0);
                  //

                }else{
            
                  launch_job(NewJob(help),1);

              }
            }
          
            
        
    }while (status);

    
}
void welcomeScreen(){
        printf("\n\t================================================\n");
        printf("\t          Group 5 :  Shell in C \n");
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

