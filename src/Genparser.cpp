
#include <unistd.h>
#include <iostream> //for debug
#include "Genparser.h"
#include "Stats.h"

Genparser::Genparser(int* fd, Stats* stats) : m_fd(fd), m_stats(stats){
    close(m_fd[1]);
}

Genparser::~Genparser(){
    close(m_fd[0]);
}

void* Genparser::threadEntry(void* caller){
    Genparser* tmp = static_cast<Genparser*>(caller);
    tmp->parse();    
}

void Genparser::parse(){

    //parse and update into m_stats
    //tmp to show out put
    char buff[10];
    int tmpCount(0);
    while(read(m_fd[0], buff, 10) != 0){
        ++tmpCount;

         std::cout<<"Read number "<<tmpCount<<": "<<buff<<"\n";
     }
}
