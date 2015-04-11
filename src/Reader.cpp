
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <thread>
#include "Reader.h"
#include "Stat.h"

const std::string getVersion();
const std::string currentTime();

Reader::Reader(std::list<Stat*> &stats, std::string fileName) 
        : m_stats(stats), m_fileName(fileName){

    if(m_fileName == "") 
        std::cout<<getVersion()<<std::endl;
    else{
        //print to file
        std::ofstream out(m_fileName, std::ofstream::app);
        //out.seekp(0, std::ios_base::beg);
        out << getVersion() << "\n";
    }
}

Reader::~Reader(){
    //clean up m_stats
    for(auto it = m_stats.begin();it!=m_stats.end();++it)
        delete (*it);    
}

void Reader::measure(){
    //call measure for each in m_stats
    //call threadentry func, so all wait periods can sync
    std::list<std::thread*> threads;

    for(auto it = m_stats.begin();it!=m_stats.end();++it){
        threads.push_back(new std::thread(Stat::threadEntry, *it));
    }
 
    //wait for threads to finish
    for(auto it = threads.begin();it!=threads.end();++it){
        (*it)->join();
    }    
}

void Reader::read(){
    //call read for each in m_stats
    //print out all the stuffs however

    //print current time each iteratino through all of the stats
    std::string st(currentTime());

    for(auto it = m_stats.begin();it!=m_stats.end();++it){
        st += (*it)->read()+"\n";
    }
    if(m_fileName == "") 
        std::cout<<st<<std::endl;
    else{
        //print to file
        std::ofstream out(m_fileName, std::ofstream::app);
        //out.seekp(0, std::ios_base::beg);
        out << st << "\n";
    }
}

const std::string getVersion(){
    std::ifstream in("/proc/version");
    std::string st;
    getline(in, st, '#');
    return st;
}

const std::string currentTime(){
    time_t t= time(0);
    tm tstruct;
    char b[80];
    tstruct = *localtime(&t);
    strftime(b, sizeof(b), "%m-%d-%Y %X\n", &tstruct);
    return b;
}
