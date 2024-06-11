#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void ouch(int sig){
    printf("OUCH! - I got signal %d\n", sig);
    (void) signal(SIGINT, SIG_DFL);
}

int main(){
    pid_t pid;
    printf("Program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            //exit(1);
        case 0:
            (void) signal(SIGINT, ouch);
            while(1) {
                printf("Hello from the child!\n");
                sleep(1);
            }
            break;
        default:
            printf("The parent is sending SIGINT to the child in 5 seconds...\n");
            sleep(5);
            kill(pid, SIGINT);
            printf("SIGTERM is sending to the child in 5 seconds\n");
            sleep(5);
            kill(pid, SIGTERM);
            break;
    }
    printf("Program ending\n");
    return 0;
}

