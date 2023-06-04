#include <stdio.h>
#include <signal.h>
#include <unistd.h> //sleep

void handler(int sig)
{
    printf("\b\b"); //não funciona mais
    write(1, "\nSIGINT received", 16);
}

int main (void)
{
    struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART; //to use sigaction with scanf
    sigaction(SIGINT, &sa, NULL);
    while (1)
    {
        sleep(1);
    }
}
//     int x;
//     printf("Input: ");
//     scanf("%d", &x);
//     printf("result = %i", x);
// }