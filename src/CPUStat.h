#ifndef CPUSTAT_H
#define CPUSTAT_H

#include "Stat.h"

class CPUStat : public Stat{
public:
    CPUStat();
    ~CPUStat();

   void measure();
   std::string read(); 

private:
    //relevant fields

};

#endif
