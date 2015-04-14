#ifndef PROCSTAT_H
#define PROCSTAT_H

#include <list>
#include <string>
#include <pthread.h>
#include <dirent.h>
#include "Stat.h"

//foward declaration
class ProcMan;

class ProcStat : public Stat {
public:
    ProcStat();
    ~ProcStat();

   void measure();
   std::string read();

   void clean();

private:
    //hold the top N processes pointers
    std::list<ProcMan*> m_top;

   //the infomation for process is taken from /proc/stat
   //or /proc/statm or /proc/status

   //Process ID
   pid_t m_pid;
   //Filename of the executable
   std::string m_comm;
   //one character from "RSDZTW", where R: running, S: sleeping,
   //D: wating, Z: zombie, T: traced/stopped, W: paging
   char m_state;
   //parent pid
   pid_t m_ppid;
   //process group ID
   pid_t m_pgrp;
   //session id
   pid_t m_session;
   //amount of time this process has been scheduled in user mode
   unsigned long m_usertime;
   //amount of time this process has been scheduled in kernel mode
   unsigned long m_kerneltime;
   //priority value
   int m_priority;
   //nice value
   int m_nice;
   //number of threads in thi sprocess
   int m_num_threads;
   //time in jiiffies (clock ticks divided by sysconf(_SC_CLK_TCK)
   //that the process started after system boot
   unsigned long long m_startime;
   //virtual memory size in bytes
   long int m_vsize;
};

#endif
