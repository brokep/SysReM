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
    ///proc/stat
    double m_nice;
    double m_user;
    double m_system;
    double m_iowait;
    double m_idle;
};

#endif
