#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/*
 * CS3305 - Assignment 1
 *
 * Created by Salman Shaikh on 2021-09-23
 * Student Number mshaik52 - 250959996
 */

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[]) {

    pid_t child_1,child_2, child_2_1;

    //create the child process and they child process pid
    child_1=fork();

    //for parent process to execute
    if(child_1>0) {
        printf("parent (PID %d) created child_1 (PID %d).\n",getpid(),child_1);
        printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2.\n",getpid(),child_1);
    }

    //for child process to execute
    if(child_1 == 0) {
        printf("child_1 (PID %d) is calling an external_program.out and leaving parent\n",getpid(),getppid());

        char externalMessage[100]="";
        sprintf(externalMessage,"%d",getpid());
        strcat(externalMessage,"for child_1");

        execl(argv[1], "",externalMessage);
        wait(NULL);
    }
    //parent will wait for child 1 to finish
    wait(NULL);

    //parent now makes child
    child_2 = fork();

    //for parent
    if(child_2 > 0) {
        printf("parent (PID %d) created child_2 (PID %d)\n", getpid(),child_2);
    }
    //for child 2 process
    if(child_2 ==0 ){
        //child 2 will create anther process
        child_2_1 = fork();

        //for child 2
        if(child_2_1 > 0){
            printf("child_2 (PID %d) created child_2.1 (PID %d)\n", getpid(), child_2_1);
            wait(NULL);
        }
        //for child_2_1
        if(child_2_1 == 0) {
            char externalMessage[100]="";
            sprintf(externalMessage,"%d",getpid());
            strcat(externalMessage,"for child_2.1");

            printf("child_2.1 (PID %d) is calling an external program external_program.out and leaving child_2.1\n",getpid());

            execl(argv[1], "",externalMessage);
            wait(NULL);
        }
    }

    //wait for child 2 to be finished
    wait(NULL);

    //if back in parent- meaning both child processes have ended. End the program.
    if(child_1 > 0 && child_2 > 0) {
        printf("child_1 and child_2 are completed and parent process is terminating…\n");
    }
    return 0;
}
