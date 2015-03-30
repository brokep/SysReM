
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "Reader.h"
#include "Stat.h"

Reader::Reader(std::list<Stat*> &stats) : m_stats(stats){
}

Reader::~Reader(){
    //clean up m_stats
    for(auto it = m_stats.begin();it!=m_stats.end();++it)
        delete (*it);    
}

void Reader::measure(){
    //call measure for each in m_stats
    for(auto it = m_stats.begin();it!=m_stats.end();++it)
        (*it)->measure();    
}

const std::string currentTime();

void Reader::read(){
    //call read for each in m_stats
    //print out all the stuffs however

    //print current time each iteratino through all of the stats
    std::cout << currentTime() << std::endl;    

    std::string st;
    for(auto it = m_stats.begin();it!=m_stats.end();++it){
        st += (*it)->read();
    } 
    std::cout<<st<<std::endl;
}


const std::string currentTime(){
    time_t t= time(0);
    tm tstruct;
    char b[80];
    tstruct = *localtime(&t);
    strftime(b, sizeof(b), "%d-%m-%Y %X", &tstruct);
    return b;
}
