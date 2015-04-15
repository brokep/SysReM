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

};

#endif
