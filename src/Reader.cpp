
#include <iomanip>
#include <ctime>
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

void Reader::read(){
    //call read for each in m_stats
    //print out all the stuffs however

    //print current time each iteratino through all of the stats
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::cout << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << std::endl; 

    std::string st;
    for(auto it = m_stats.begin();it!=m_stats.end();++it){
        st += (*it)->read();
    } 
    std::cout<<st<<std::endl;
}
