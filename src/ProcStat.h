#ifndef PROCSTAT_H
#define PROCSTAT_H

#include "Stat.h"

class ProcStat : public Stat{
public:
    ProcStat();
    ~ProcStat();

   void measure();
   std::string read(); 

private:
    //relevant fields

};

#endif
