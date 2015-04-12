#ifndef DISKSTAT_H
#define DISKSTAT_H

#include <list>
#include "Stat.h"

//foward declaration
class DevMan;

class DiskStat : public Stat{
public:
    DiskStat();
    ~DiskStat();

   void measure();
   std::string read(); 

private:
    std::list<DevMan*> m_devs;

};

#endif
