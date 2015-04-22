#ifndef STATGEN_H
#define STATGEN_H

#include <list>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "Stat.h"
#include "CPUStat.h"
#include "MemStat.h"
#include "DiskStat.h"
#include "ProcStat.h"

#define CPU_UTIL 0
#define MEM_UTIL 1
#define DISK_STAT 2 
#define PROC_TOP 3 

#define MEASURE_RES 900 //ms to measure stats
#define NUM_TOPPROC 3 //default number of top processes to display

#define DEFAULT_INTERVAL 1
#define DEFAULT_COUNT 10
#define DEFAULT_FILENAME "output"

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

    static  std::list<int> genlist(int count, char** args){
        std::list<int> statlist;
        for(int i = 0;i<count;++i){
            switch(args[i][1]){
                case 'c':statlist.push_back(CPU_UTIL);break;
                case 'm':statlist.push_back(MEM_UTIL);break;
                case 'd':statlist.push_back(DISK_STAT);break;
                case 'p':statlist.push_back(PROC_TOP);break;
                case 'a':
                    statlist.push_back(CPU_UTIL);
                    statlist.push_back(MEM_UTIL);
                    statlist.push_back(DISK_STAT);
                    statlist.push_back(PROC_TOP);break;
                case 'f':
                    //output to file
                    //look for file name
                    if(i+1==count || args[i+1][0] == '-'){
                        //not present, use default name
                        FILE_NAME = DEFAULT_FILENAME; 
                    }
                    //file name present, grab it and store
                    else{
                        FILE_NAME = args[i+1]; 
                        //this arg is now used, so skip it next iteration
                        ++i;
                    }
                    break;
                case 'n':
                    if(i+1==count || args[i+1][0] == '-'){
                        //no count presesnt
                        std::cout<<"arg -n must be followed by a number\n";
                        exit(-1);
                    }
                    //file name present, grab it and store
                    else{
                        TOP_PROCS = atoi(args[i+1]); 
                        //this arg is now used, so skip it next iteration
                        ++i;
                    }
                    break;
            }
        } 
        if(statlist.size() == 0){   //if no vlues in the thing, use all/default vals
            char* tmp[1];
            tmp[0] = (char*)std::string("-a").c_str();
            statlist = genlist(1, tmp);
        }
        statlist.sort(); //put all vals in default order
        statlist.unique(); //remove duplicates

        return statlist;
    } 
    static std::string FILE_NAME;
    static int TOP_PROCS;
};

#endif
