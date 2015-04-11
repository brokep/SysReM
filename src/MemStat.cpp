#include <fstream>
#include <cstdio>
#include <cstring>
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

    do{
        if(strcmp(b,"MemTotal:") == 0){
            in>>memTotal;
        }
        else if(strcmp(b,"MemFree:") == 0){
            in>>memFree;
        }
        else if(strcmp(b,"Buffers:") == 0){
            in>>buffers;
        }
        else if(strcmp(b,"Cached:") == 0){
            in>>cached;
        }
        else if(strcmp(b,"SwapTotal:") == 0){
            in>>swapTotal;
        }
        else if(strcmp(b,"SwapFree:") == 0){
            in>>swapFree;
        }

        in>>b;
    } while(in.peek() != EOF);
    
}

std::string MemStat::read(){
    char a[100];
    char b[6][100];
    char ret[700];
    sprintf(a,"Memory Utilization(kB)\n");
    sprintf(b[0], "Free Memory:  %10d kB (%06.2f%c)\n", memFree, (100.0*memFree/memTotal),'%');
    sprintf(b[1], "Total Memory: %10d kB\n", memTotal);
    sprintf(b[2], "Buffers:      %10d kB\n", buffers);
    sprintf(b[3], "Cached:       %10d kB\n", cached);
    sprintf(b[4], "Swap Free:    %10d kB (%06.2f%c)\n", swapFree, (100.0*swapFree/swapTotal),'%');
    sprintf(b[5], "Swap Total:   %10d kB\n", swapTotal);
    sprintf(ret, "%s%s%s%s%s%s%s",a,b[0],b[1],b[2],b[3],b[4],b[5]);
    return ret;
}
