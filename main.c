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

    char c =5;
    //create the child process and they child process pid
    child_1=fork();

    //for parent process to execute
    if(child_1>0) {
        printf("Parent process created child with pid: %d, parent pid is: %d.\n",child_1,getpid());
    }

    //for child process to execute
    if(child_1 == 0) {
        printf("I am child 1 my pid is: %d, and my parents pid is: %d\n",getpid(),getppid());


        //TODO call an external program...
        execl(argv[1], "",NULL);
        wait(NULL);
    }

    //parent will wait for child 1 to finish
    wait(NULL);

    //parent now makes child
    child_2 = fork();

    //for parent
    if(child_2 > 0) {
        printf("child_2 has been made with pid: %d\n", child_2);
    }
    //for child 2 process
    if(child_2 ==0 ){
        //child 2 will create anther process
        child_2_1 = fork();

        //for child 2
        if(child_2_1 > 0){
            printf("child_2_1 has been made with pid %d\n", child_2_1);
        }
        //for child_2_1
        if(child_2_1 == 0) {
            //TODO child_2_1 will call external program here
            //TODO call an external program...
            execl(argv[1], "",NULL);
            wait(NULL);
        }
    }

    //wait for child 2 to be finished
    wait(NULL);

    //if back in parent- meaning both child processes have ended. End the program.
    if(child_1 > 0 && child_2 > 0) {
        printf("ending process\n");
        exit(0);
    }
    return 0;
}
