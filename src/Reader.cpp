
#include "Reader.h"

Reader::Reader(std::list<Stat*> &stats) : m_stats(stats){
}

Reader::~Reader(){
    //clean up m_stats
}

void Reader::measure(){
    //call measure for each in m_stats
}

void Reader::read(){
    //call read for each in m_stats
    //print out all the stuffs however
}
