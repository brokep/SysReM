#include <iostream>
#include <stdlib.h>
#include "StatGen.h"
#include "Reader.h"
#include "Timer.h"

//default file name is output
std::string StatGen::FILE_NAME = "";
int StatGen::TOP_PROCS = 4;

int main(int argc, char** argv){
    
    int intv;
    int count;
    //if passed two arguemts, use those values
    //otherwise, use defualt values
    bool f(argc >=3);
    intv = f?atoi(argv[1]):DEFAULT_INTERVAL;
    count = f?atoi(argv[2]):DEFAULT_COUNT; 

    std::list<int> statlist(StatGen::genlist(argc-3, argv+3));
    
    std::list<Stat*> stats(StatGen::generate(statlist)); 

    Reader r(stats, StatGen::FILE_NAME);
    Timer t(r, intv, count);

    t.start();

    return 0;
}
