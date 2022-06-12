#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include "job.h"
#include "global.h"
#include "builtin.h"

// import job structure
typedef struct job job;
/* A process is a single process.  */
typedef struct process
{
  struct process *next;       /* next process in pipeline */
  char **argv;                /* for exec */
  pid_t pid;                  /* process ID */
  char completed;             /* true if process has completed */
  char stopped;               /* true if process has stopped */
  int status;                 /* reported status value */
} process;

process *NewProcess(char *commande,job *j);



void launch_process (process *p, pid_t pgid, int infile, int outfile, int errfile,int foreground);

int mark_process_status (pid_t pid, int status);

void update_status (void);

int check_builtin_process(char** argv);
#endif //PROCESS_H