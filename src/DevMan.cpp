
#include <fstream>
#include <cstring>
#include <cstdio>
#include "DevMan.h"
#include "StatGen.h"

DevMan::DevMan(std::string devName, int pos):m_devName(devName), m_pos(pos){
}

DevMan::~DevMan(){
}

void DevMan::readBefore(){
    std::ifstream in("/proc/diskstats");
    in.seekg(m_pos);
   
    char devnull[100];//for trash 
    in >> reads[0];
    in >> devnull;
    in >> sectors_read[0];
    in >> devnull;
    in >> writes[0];
    in >> devnull;
    in >> sectors_writ[0];
}

void DevMan::readAfter(){
    std::ifstream in("/proc/diskstats");
    in.seekg(m_pos);
   
    char devnull[100];//for trash 
    in >> reads[1];
    in >> devnull;
    in >> sectors_read[1];
    in >> devnull;
    in >> writes[1];
    in >> devnull;
    in >> sectors_writ[1];
}

std::string DevMan::print(){
    double seconds(MEASURE_RES/1000.0);//number or seconds between reads
    char buff[200];
    sprintf(buff, "%16s%12s%12d%12d%12d%12d\n","",m_devName.c_str(), (int)((reads[1]-reads[0])/seconds), 
                                                      (int)((sectors_read[1]-sectors_read[0])/seconds), 
                                                      (int)((writes[1]-writes[0])/seconds),
                                                      (int)((sectors_writ[1]-sectors_writ[0])/seconds));
    return buff;    
}
