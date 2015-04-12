
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <algorithm>
#include <memory>
#include "DiskStat.h"
#include "DevMan.h"
#include "StatGen.h"

DiskStat::DiskStat(){
}

DiskStat::~DiskStat(){
    std::for_each(m_devs.begin(), m_devs.end(), std::default_delete<DevMan>());
    m_devs.clear();
}


void DiskStat::measure(){
    //memory specific measurements 
    //clear ant previos devices
    std::for_each(m_devs.begin(), m_devs.end(), std::default_delete<DevMan>());
    m_devs.clear();    

    std::ifstream in("/proc/diskstats"); 
    char b[50];
    in>>b;
    //find all devices, so those that start with sd
    do{
        if(strlen(b)>2){
            if(b[0]=='s' && b[1]=='d'){
                m_devs.push_back(new DevMan(b, in.tellg())); 
            }
        }  

        in>>b;
    } while(in.peek() != EOF);
    
    //then call inital read on all
    for(auto it=m_devs.begin();it!=m_devs.end();++it)
        (*it)->readBefore();

    //wait the appropriate amount
    usleep(1000*MEASURE_RES); 

    //read again after
    for(auto it=m_devs.begin();it!=m_devs.end();++it)
        (*it)->readAfter();
}

std::string DiskStat::read(){
    char b[200];
    sprintf(b, "%16s%12s%12s%12s%12s%12s\n","Disk Utilization", "device", "reads/sec",
                                      "sctrR/sec", "writes/sec", "sctrW/sec");
   std::string ret(b);

    for(auto it=m_devs.begin();it!=m_devs.end();++it)
        ret += (*it)->print();

    return ret;
}
