#include <iostream>
#include <unistd.h> //for pipe
#include <stdio.h> //perror
#include <pthread.h>
#include "Statgen.h"
#include "Stats.h"
#include "Genparser.h"

int main(int argc, char** argv){


    int pipefd[2];
    
    if(pipe(pipefd) != 0){
        perror("pipe ");
        return -1;
    }
    
    pid_t pid = fork();

    if(pid>0){
        Statgen sar(pipefd, 1, 10);
        sar.start();

        _exit(0);
    }
    else if(pid == 0){
        Stats stats;
        Genparser parser(pipefd, &stats);

        //thread into parser 
        pthread_t parseThread;
         
        if(pthread_create(&parseThread, NULL, 
            Genparser::threadEntry, &parser) !=0){

            perror("parser thread");
        }     

        
        //continuous outpute based on stats



        //join sometime, havent worked thisa out yet
        if(pthread_join(parseThread, NULL)!=0){
            perror("parseThread join"); 

        } 
        
    }
    else{
        perror("fork");
    } 

    return 0;
}
