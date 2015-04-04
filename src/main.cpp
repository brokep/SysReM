#include <iostream>
#include <stdlib.h>
#include "StatGen.h"
#include "Reader.h"
#include "Timer.h"

#define DEFAULT_INTERVAL 1
#define DEFAULT_COUNT 10

int main(int argc, char** argv){
    
    int intv;
    int count;
    //if passed two arguemts, use those values
    //otherwise, use defualt values
    bool f(argc ==3);
    intv = f?atoi(argv[1]):DEFAULT_INTERVAL;
    count = f?atoi(argv[2]):DEFAULT_COUNT; 

    std::list<int> statlist;
    statlist.push_back(CPU_UTIL);
    statlist.push_back(MEM_UTIL);
    statlist.push_back(DISK_STAT);
    statlist.push_back(PROC_TOP);
    
    std::list<Stat*> stats(StatGen::generate(statlist)); 

    Reader r(stats);
    Timer t(r, intv, count);

    t.start();

    return 0;
}
