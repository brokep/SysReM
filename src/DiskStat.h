#ifndef DISKSTAT_H
#define DISKSTAT_H

#include "Stat.h"

class DiskStat : public Stat{
public:
    DiskStat();
    ~DiskStat();

   void measure();
   std::string read(); 

private:
    //relevant fields

};

#endif
