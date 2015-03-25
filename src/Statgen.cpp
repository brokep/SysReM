#include <unistd.h>
#include <stdio.h>
#include <string>
#include "Statgen.h"


Statgen::Statgen(int* fd, int interval, int count) 
  : m_fd(fd), m_interval(interval), m_count(count) {

    close(m_fd[0]);
    dup2(m_fd[1], STDOUT_FILENO);    
}
    
Statgen::~Statgen(){ 
    close(m_fd[1]);
}

void Statgen::start(){
    execlp("sar", "sar", std::to_string(m_interval).c_str(), 
        std::to_string(m_count).c_str(), NULL);
 
}
