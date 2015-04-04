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

    ///proc/stat
    double m_nice;
    double m_user;
    double m_system;
    double m_iowait;
    double m_idle;
};

#endif
