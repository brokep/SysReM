#include <cstdio>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include "ProcMan.h"
#include "StatGen.h"


ProcMan::ProcMan(int pidDir) : m_pidDir(pidDir), m_bticks(0), m_ticks(0){
}

void ProcMan::readBefore(){
    //read values 14 and 15 in m_pidDir/stat
    char fn[50];
    sprintf(fn,"%s%d%s", "/proc/", m_pidDir, "/stat");
    std::ifstream in(fn);

    for(int i=1; i<14; ++i){
        in.ignore(100, ' ');
    } 
    //sum them and store into m_bticks
    int utime(0), stime(0);
    in>>utime;
    in>>stime;
    m_bticks = utime + stime;
}

void ProcMan::readAfter(){
    //read again vals 14, 15 and sum
    char fn[50];
    sprintf(fn,"%s%d%s", "/proc/", m_pidDir, "/stat");
    std::ifstream in(fn);   

    for(int i=1; i<14; ++i){
        in.ignore(100, ' ');
    } 

    //calc subtract m_bticks and store result in m_ticks
    int utime, stime;
    in>>utime;
    in>>stime;
    m_ticks = utime + stime;
    m_ticks -= m_bticks;
}

bool ProcMan::operator<(ProcMan& rhs){
    return m_ticks < rhs.m_ticks; 
}

std::string ProcMan::print(){
    //measure all appropraite   params based on m_pidDir 
    int pid;
    char command[100];
    double cpu(0);
    double mem(0);

    char fn[50];
    sprintf(fn,"%s%d%s", "/proc/", m_pidDir, "/status");
    std::ifstream in(fn);   

    char b[50];
    do{
        in>>b;
        if(strcmp(b,"Name:") == 0){
            in>>command;
        }
        else if(strcmp(b,"Pid:") == 0){
            in>>pid;
        }
        else if(strcmp(b,"VmRSS") == 0){
            in>>mem;
        }

    } while(in.peek() != EOF);
    
    double totalmem(0);
    std::ifstream in2("/proc/meminfo");
    

    do{
        in2>>b;
        if(strcmp(b,"MemTotal:") == 0){
            in2>>totalmem;
            break;
        }
    } while(in.peek() != EOF);
 
    mem = (mem/totalmem)*100;


    int cores(0);
    std::ifstream in3("/proc/cpuinfo");

    do{
        in3>>b;
        if(strcmp(b,"cpu") == 0){
            in3>>b;
            if(strcmp(b,"cores") == 0){
                in3>>b;
                in3>>cores;
                break;
            }
        }
    } while(in.peek() != EOF);
 
    //cpu = (1.0*m_ticks/(cores * sysconf(_SC_CLK_TCK))) / (MEASURE_RES/1000.0);
    cpu = m_ticks; //TODO

    //format string and return one line of process info
    char ret[200];
    sprintf(ret, "%15s%5d%15s%6.2f%6.2f\n","",pid,command,cpu,mem);
    return ret;
}

