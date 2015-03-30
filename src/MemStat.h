#ifndef MEMSTAT_H
#define MEMSTAT_H

#include "Stat.h"

class MemStat : public Stat{
public:
    MemStat();
    ~MemStat();

   void measure();
   std::string read(); 

private:
    //relevant fields

};

#endif
