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


class StatGen{
public:
    static  std::list<Stat*> generate(std::list<int> statlist){
        //generate list of Stat classes based on statlist
        std::list<Stat*> stats;
        for(auto it = statlist.begin();it!=statlist.end();++it){
            switch(*it){
                case CPU_UTIL:stats.push_front(new CPUStat());break;
                case MEM_UTIL:stats.push_front(new MemStat());break;
                case DISK_STAT:stats.push_front(new DiskStat());break;
                case PROC_TOP:stats.push_front(new ProcStat());break;

            }

        } 

        return stats;
    } 
};

#endif
