/*
 * =====================================================================================
 *
 *       Filename:  wait.c
 *
 *    Description:  learn how fork()/wait() work.
 *
 *        Version:  1.0
 *        Created:  01/16/2020 09:47:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
        Reference:  http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/wait.html
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100

void  ChildProcess(char [], char []);    /*  child process prototype  */

int main(void)
{
  pid_t   pid1, pid2, pid;
  int     status;
  char    buf[BUF_SIZE];

  printf("*** Parent is about to fork process 1 ***\n");
  // fork() returns value < 0 when failed
  if ((pid1 = fork()) < 0) {
    printf("Failed to fork process 1\n");
    exit(1);
  }
  // fork() returns 0 to child process when successful
  else if (pid1 == 0) 
    ChildProcess("First", "   ");

  printf("*** Parent is about to fork process 2 ***\n");
  if ((pid2 = fork()) < 0) {
    printf("Failed to fork process 2\n");
    exit(1);
  }
  else if (pid2 == 0) 
    ChildProcess("Second", "      ");

  sprintf(buf, "*** Parent enters waiting status .....\n");
  // printf() is buffered, so using write()
  // or use fflush() is fine too?
  write(1, buf, strlen(buf));
  // only parent can reach to this point
  // wait() will suspend parent until one of its children exits
  // when this happens, wait() will receive wstatus information from child
  // wait() itself will return the child's pid when it returns.
  pid = wait(&status);
  sprintf(buf, "*** Parent detects process %d was done ***\n", pid);
  write(1, buf, strlen(buf));
  // here we have another wait() awaiting another child process to quit
  pid = wait(&status);
  printf("*** Parent detects process %d is done ***\n", pid);
  printf("*** Parent exits ***\n");
  exit(0);
}

void  ChildProcess(char *number, char *space)
{
  pid_t  pid;
  int    i;
  char   buf[BUF_SIZE];

  // child process gets its process id
  pid = getpid();
  sprintf(buf, "%s%s child process starts (pid = %d)\n", 
      space, number, pid);
  write(1, buf, strlen(buf));
  // child prints out number from 1 - 200, pretending it is doing some real work
  for (i = 1; i <= MAX_COUNT; i++) {
    sprintf(buf, "%s%s child's output, value = %d\n", space, number, i); 
    write(1, buf, strlen(buf));
  }
  sprintf(buf, "%s%s child (pid = %d) is about to exit\n", 
      space, number, pid);
  write(1, buf, strlen(buf));     
  exit(0);
}
