#include <fstream>
#include <cstdio>
#include "MemStat.h"

MemStat::MemStat(){
}

MemStat::~MemStat(){
}


void MemStat::measure(){
    //memory specific measurements 
    using std::ifstream;
    ifstream in("/proc/meminfo");
    
    char b[50];
    in>>b;
    in>>memTotal;
    in>>b;
    in>>b;
    in>>memFree;
    in>>b;
    in>>b;
    in>>buffers;
    in>>b;
    in>>b;
    in>>cached;
    in>>b;
    
    for(int i=0;i<(13*3);++i){
        in>>b;
    }
    
    in>>b;
    in>>swapTotal;
    in>>b;
    in>>b;
    in>>swapFree;
}

std::string MemStat::read(){
    char a[100];
    char b1[100];
    char b2[100];
    char b3[100];
    char b4[100];
    char b5[100];
    char b6[100];
    char ret[700];
    sprintf(a,"Memory Utilization(kB)\n");
    sprintf(b1, "Free Memory:  %10d kB (%06.2f%c)\n", memFree, (100.0*memFree/memTotal),'%');
    sprintf(b2, "Total Memory: %10d kB\n", memTotal);
    sprintf(b3, "Buffers:      %10d kB\n", buffers);
    sprintf(b4, "Cached:       %10d kB\n", cached);
    sprintf(b5, "Swap Free:    %10d kB (%06.2f%c)\n", swapFree, (100.0*swapFree/swapTotal),'%');
    sprintf(b6, "Swap Total:   %10d kB\n", swapTotal);
    sprintf(ret, "%s%s%s%s%s%s%s",a,b1,b2,b3,b4,b5,b6);
    return ret;
}
