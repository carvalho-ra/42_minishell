#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> //exit

// SIGQUIT is ctr + "\"
//got to ignore this signal in all program

// ctrl+D is not a signal
// how to cach it?
// scanf? scan?

void sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\b\breceived SIGINT\n"); // "\b" mutes char from signal print "^C"
        //bach clears readline, prints "\n" and a new prompt
        exit (1);
    }
    else if (sig == SIGQUIT)
    {
        printf("\b\b");
        //do nothing
        //still prints "^D" and get stucked 
        //bash does absolutley nothing
        exit (1);
    }
}

int main(void)
{
  if (signal(SIGINT, &sig_handler) == SIG_ERR)
  printf("\ncan't catch SIGINT\n");
//signal(SIGQUIT, SIG_IGN);

if (signal(SIGQUIT, &sig_handler) == SIG_ERR)
    printf("\ncan't catch SIGINT\n");
  while(1)
    // wait so computer doesen't become slow
    sleep(1);
  return 0;
}