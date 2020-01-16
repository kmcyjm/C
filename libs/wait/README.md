The wait() System Call
======================

The system call **wait()** is easy. This function blocks the calling process until one of its _child_ processes exits or
a signal is received. For our purpose, we shall ignore signals. **wait()** takes the address of an integer variable and
returns the process ID of the completed process. Some flags that indicate the completion status of the child process are
passed back with the integer pointer. One of the main purposes of **wait()** is to wait for completion of child
processes.

The execution of **wait()** could have two possible situations.

1. If there are at least one child processes running when the call to **wait()** is made, the caller will be blocked
until one of its child processes exits. At that moment, the caller resumes its execution.
1. If there is no child process running when the call to **wait()** is made, then this **wait()** has no effect at
all. That is, it is as if no **wait()** is there.

Consider the following program. Click [**here**](fork-03.c) to download a copy of this file **fork-03.c**.

```c
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX\_COUNT  200
#define   BUF\_SIZE   100

void  ChildProcess(char \[\], char \[\]);    /\* child process prototype  \*/

void  main(void)
{
  pid\_t   pid1, pid2, pid;
  int     status;
  int     i;
  char    buf\[BUF\_SIZE\];

  printf("\*\*\* Parent is about to fork process 1 \*\*\*\\n");
  if ((pid1 = fork()) < 0) {
    printf("Failed to fork process 1\\n");
    exit(1);
  }
  else if (pid1 == 0) 
    ChildProcess("First", "   ");

  printf("\*\*\* Parent is about to fork
      process 2 \*\*\*\\n");
  if ((pid2 = fork()) < 0) {
    printf("Failed to fork
        process 2\\n");
    exit(1);
  }
  else
    if
      (pid2
       ==
       0) 
        ChildProcess("Second",
            "
            ");

  sprintf(buf,
      "\*\*\*
      Parent
      enters
      waiting
      status
      .....\\n");
  write(1,
      buf,
      strlen(buf));
  pid
    =
    wait(&status);
  sprintf(buf,
      "\*\*\*
      Parent
      detects
      process
      %d
      was
      done
      \*\*\*\\n",
      pid);
  write(1,
      buf,
      strlen(buf));
  pid
    =
    wait(&status);
  printf("\*\*\*
      Parent
      detects
      process
      %d
      is
      done
      \*\*\*\\n",
      pid);
  printf("\*\*\*
      Parent
      exits
      \*\*\*\\n");
  exit(0);
}

void  ChildProcess(char \*number, char \*space)
{
  pid\_t  pid;
  int    i;
  char   buf\[BUF\_SIZE\];

  pid = getpid();
  sprintf(buf, "%s%s child process starts (pid = %d)\\n", 
      space, number, pid);
  write(1, buf, strlen(buf));
  for (i = 1; i <= MAX\_COUNT; i++) {
    sprintf(buf, "%s%s child's output, value = %d\\n", space, number, i); 
    write(1, buf, strlen(buf));
  }
  sprintf(buf, "%s%s child (pid = %d) is about to
      exit\\n", 
      space, number, pid);
  write(1, buf, strlen(buf));     
  exit(0);
}
```

This program shows some typical process programming techniques. The main program creates two child processes to execute
the same printing loop and display a message before exit. For the parent process (_i.e._, the main program), after
creating two child processes, it enters the wait state by executing the system call **wait()**. Once a child exits, the
parent starts execution and the ID of the terminated child process is returned in **pid** so that it can be printed.
There are two child processes and thus two **wait()**s, one for each child process. In this example, we do not use the
returned information in variable **status**.

However, the parent does not have to wait immediately after creating all child processes. It may do some other tasks.
The following is an example. Click [**here**](fork-04.c) for this file **fork-04.c**.
```c
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX\_COUNT  200
#define   BUF\_SIZE   100

void  ChildProcess(char \[\], char \[\]);    /\* child process prototype  \*/
void  ParentProcess(void);               /\* parent process prototype \*/

void  main(void)
{
  pid\_t   pid1, pid2, pid;
  int     status;
  int     i;
  char    buf\[BUF\_SIZE\];

  printf("\*\*\* Parent is about to fork process 1 \*\*\*\\n");
  if ((pid1 = fork()) < 0) {
    printf("Failed to fork process 1\\n");
    exit(1);
  }
  else if (pid1 == 0) 
    ChildProcess("First", "   ");

  printf("\*\*\* Parent is about to fork
      process 2 \*\*\*\\n");
  if ((pid2 = fork()) < 0) {
    printf("Failed to fork
        process 2\\n");
    exit(1);
  }
  else
    if
      (pid2
       ==
       0) 
        ChildProcess("Second",
            "
            ");

  ParentProcess();
  sprintf(buf,
      "\*\*\*
      Parent
      enters
      waiting
      status
      .....\\n");
  write(1,
      buf,
      strlen(buf));
  pid
    =
    wait(&status);
  sprintf(buf,
      "\*\*\*
      Parent
      detects
      process
      %d
      was
      done
      \*\*\*\\n",
      pid);
  write(1,
      buf,
      strlen(buf));
  pid
    =
    wait(&status);
  printf("\*\*\*
      Parent
      detects
      process
      %d
      is
      done
      \*\*\*\\n",
      pid);
  printf("\*\*\*
      Parent
      exits
      \*\*\*\\n");
  exit(0);
}

#define  QUAD(x)  (x\*x\*x\*x)

void  ParentProcess(void)
{
  int  a, b, c, d;
  int  abcd, a4b4c4d4;
  int  count = 0;
  char buf\[BUF\_SIZE\];

  sprintf(buf, "Parent is about to compute the Armstrong numbers\\n");
  write(1, buf, strlen(buf));
  for (a = 0; a <= 9; a++)
    for (b = 0; b <= 9; b++)
      for (c = 0; c <= 9; c++)
        for (d = 0; d <= 9; d++) {
          abcd
            =
            a\*1000
            +
            b\*100
            +
            c\*10
            + d;
          a4b4c4d4
            =
            QUAD(a)
            +
            QUAD(b)
            +
            QUAD(c)
            +
            QUAD(d);
          if
            (abcd
             ==
             a4b4c4d4)
            {
              sprintf(buf,
                  "From
                  parent:
                  "
                  "the
                  %d
                  Armstrong
                  number
                  is
                  %d\\n",
                  ++count,
                  abcd);
              write(1,
                  buf,
                  strlen(buf));
            }
        }
  sprintf(buf,
      "From
      parent:
      there
      are
      %d
      Armstrong
      numbers\\n",
      count);
  write(1,
      buf,
      strlen(buf));
}

void  ChildProcess(char \*number, char \*space)
{
  pid\_t  pid;
  int    i;
  char   buf\[BUF\_SIZE\];

  pid = getpid();
  sprintf(buf, "%s%s child process starts (pid = %d)\\n", 
      space, number, pid);
  write(1, buf, strlen(buf));
  for (i = 1; i <= MAX\_COUNT; i++) {
    sprintf(buf, "%s%s child's output, value = %d\\n", 
        space, number, i); 
    write(1, buf, strlen(buf));
  }
  sprintf(buf, "%s%s child (pid = %d) is about to
      exit\\n", 
      space, number, pid);
  write(1, buf, strlen(buf));
  exit(0);
}
```

The main program creates two child processes. Both processes call function **ChildProcess()**. The main program, the
parent process, calls function **ParentProcess()**. This function computes all Armstrong numbers in the range of 0 and
9999. An Armstrong number in the range of 0 and 9999 is an integer whose value is equal to the sum of its digits raised
to the fourth power. After this, the parent enters the wait state, waiting for the completion of its child
processes. Note that since we have two processes running concurrently, we have no way to predict which one will
terminate first and hence waiting for a specific child process is a risky move. This is why we don't have a
"specific" wait in all of the previous programs.

**Warning: Although theoretically you can create as many processes as you want, systems always have some limits.
Therefore, always check to see if the returned value of **fork()** is negative and report the result. If this does
happen, try to reduce the number of child processes, or re-organize your program.**

If the returned pid is unimportant, we can treat function **wait()** as a procedure. The following code is a
simple modification to the last few statements (in the main function) of the previous example.
```c
sprintf(buf, "\*\*\* Parent enters waiting status .....\\n");
write(1, buf, strlen(buf));
wait(&status);
sprintf(buf, "\*\*\* Parent detects a child process was done \*\*\*\\n");
write(1, buf, strlen(buf));
wait(&status);
printf("\*\*\* Parent detects another child process was done \*\*\*\\n");
printf("\*\*\* Parent exits \*\*\*\\n");
```

Click [**here**](fork-05.c) to download a copy of this modified program (file **fork-05.c**).
