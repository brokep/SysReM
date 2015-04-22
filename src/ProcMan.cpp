#include <cstdio>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <stdexcept>
#include "ProcMan.h"
#include "StatGen.h"

//number of parameters in "cpu/cpuinfo" that we are going
//add to our total cpu ticks
const int CPU_PARA = 4;

ProcMan::ProcMan(int pidDir) : m_pidDir(pidDir), m_bticks(0), m_ticks(0), 
                               cpu_ticks(0) {
}

void ProcMan::readBefore(){
    //read values 14 and 15 in m_pidDir/stat
    char fn[50];
    sprintf(fn,"%s%d%s", "/proc/", m_pidDir, "/stat");
    std::ifstream in(fn);
    if (in.fail()) {
      throw std::invalid_argument("Error opening file");
      exit(1);
    }

    for(int i=1; i<14; ++i){
        in.ignore(100, ' ');
    } 
    //sum them and store into m_bticks
    int utime(0), stime(0);
    in>>utime;
    in>>stime;
    m_bticks = utime + stime;
    in.close();

    std::ifstream cpuin("/proc/stat");
    if(cpuin.fail()) {
      throw std::invalid_argument("Error opening file");
      exit(1);
    }

    char ch[5];
    int cpu_para[CPU_PARA];
    cpuin >> ch;
    for (int i = 0; i < CPU_PARA; ++i) {
      cpuin >> cpu_para[i];
      cpu_ticks += cpu_para[i];
    }
    cpuin.close();
}

void ProcMan::readAfter(){
    //read again vals 14, 15 and sum
    char fn[50];
    sprintf(fn,"%s%d%s", "/proc/", m_pidDir, "/stat");
    std::ifstream in(fn);
    if (in.fail()) {
      throw std::invalid_argument("Error opening file.");
      exit(1);
    }  

    for(int i=1; i<14; ++i){
        in.ignore(100, ' ');
    } 

    //calc subtract m_bticks and store result in m_ticks
    int utime, stime;
    in>>utime;
    in>>stime;
    m_ticks = utime + stime;
    m_ticks -= m_bticks;

    in.close();

    std::ifstream cpuin("/proc/stat");
    if(cpuin.fail()) {
      throw std::invalid_argument("Error opening /proc/stat");
      exit(1);
    }

    char ch[5];
    int cpu_para[CPU_PARA];
    cpuin >> ch;
    for (int i = 0; i < CPU_PARA; ++i) {
      cpuin >> cpu_para[i];
      cpu_ticks -= cpu_para[i];
    }

    cpu_ticks = -cpu_ticks;
    cpuin.close();
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
    if (in.fail()) {
      throw std::invalid_argument("Error opening file");
      exit(1);
    }  

    char b[50];
    do{
        in>>b;
        if(strcmp(b,"Name:") == 0){
            in>>command;
        }
        else if(strcmp(b,"Pid:") == 0){
            in>>pid;
        }
        else if(strcmp(b,"VmRSS:") == 0){
            in>>mem;
        }

    } while(in.peek() != EOF);
    in.close();
    
    double totalmem(0);
    std::ifstream in2("/proc/meminfo");
    if (in2.fail()) {
      throw std::invalid_argument("Error opening /proc/meminfo");
      exit(1);
    }    

    do{
        in2>>b;
        if(strcmp(b,"MemTotal:") == 0){
            in2>>totalmem;
            break;
        }
    } while(in2.peek() != EOF);
    in2.close();

    mem = (mem/totalmem)*100;

    int cores(0);
    std::ifstream in3("/proc/cpuinfo");
    if (in3.fail()) {
      throw std::invalid_argument("Error opening file /proc/cpuinfo");
      exit(1);
    }

    do{
        in3>>b;
        if (strcmp(b, "cores") == 0) {
          in3 >> b;
          in3 >> cores;
          break;
        }
    } while(in3.peek() != EOF);
    in3.close();
 
    //calculating the cpu utilization of the process
    //by multiplying delta tick of the process with number of cores
    //and then divides by the total cpu ticks
    cpu = (100.0 * m_ticks * cores) / cpu_ticks;

    //format string and return one line of process info
    char ret[200];
    sprintf(ret, "%15s%5d%18s%6.2f%6.2f\n","",pid,command,cpu,mem);
    return ret;
}

