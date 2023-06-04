#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/errno.h>

void handler(int sigtype)
{
    printf("got signal - %d\n", sigtype);
}

int main(void)
{
    struct sigaction act;
    int n;
    int p[2] = {};
    char buf[1000];

    pipe(p);
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    while (1)
    {
        n = read(p[0], buf, 1000);
        printf("read return = %d, errno = %d\n", n, errno);
    }
}