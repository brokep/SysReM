#ifndef CPUSTAT_H
#define CPUSTAT_H

#include "Stat.h"
#include <string>

class CPUStat : public Stat{
public:
    CPUStat();
    ~CPUStat();

   void measure();
   std::string read(); 

private:
    //information about cpu is taken from /proc/cpuinfo
   std::string m_vendor;
   std::string m_model_name;
   double m_freq;
   int m_procesors;
};

#endif
