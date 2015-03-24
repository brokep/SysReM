#include <iostream>
#include <unistd.h> //for pipe
#include <stdio.h> //perror

int main(int argc, char** argv){


    int pipefd[2];
    
    if(pipe(pipefd) != 0){
        perror("pipe ");
        return -1;
    }
    
    pid_t pid = fork();

    if(pid>0){
        //child
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        
        //printf("child stuff blahblahblah");
        execlp("sar", "sar", "5", "10", NULL);
        close(pipefd[1]);
        _exit(0);
    }
    else if(pid == 0){
        //parent
        close(pipefd[1]);
        char buff[10];
        int tmpCount(0);
        while(read(pipefd[0], buff, 10) != 0){
            ++tmpCount;

            std::cout<<"Read number "<<tmpCount<<": "<<buff<<"\n";
        }
        
    }
    else{
        perror("fork");
    } 

    return 0;
}
