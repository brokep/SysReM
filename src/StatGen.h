#ifndef STATGEN_H
#define STATGEN_H

#include <list>
#include "Stat.h"
#include "CPUStat.h"
#include "MemStat.h"
#include "DiskStat.h"
#include "ProcStat.h"

#define CPU_UTIL 0
#define MEM_UTIL 1
#define DISK_STAT 2 
#define PROC_TOP 3 

#define MEASURE_RES 200 //ms to measure stats


class StatGen{
public:
  //generate a list of Stat classes based on statlist
    static  std::list<Stat*> generate(std::list<int> statlist){
        std::list<Stat*> stats;
        for(auto it = statlist.begin();it!=statlist.end();++it){
            switch(*it){
                case CPU_UTIL:stats.push_back(new CPUStat());break;
                case MEM_UTIL:stats.push_back(new MemStat());break;
                case DISK_STAT:stats.push_back(new DiskStat());break;
                case PROC_TOP:stats.push_back(new ProcStat());break;

            }

        } 

        return stats;
    } 
};

#endif
