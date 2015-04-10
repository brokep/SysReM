#include "ProcMan.h"

ProcMan::ProcMan(char* pidDir) : m_pidDir(pidDir), m_bticks(0), m_ticks(0){
}

void ProcMan::readBefore(){
    //read values 14 and 15 in m_pidDir/stat
    //sum them and store into m_bticks
}

void ProcMan::readAfter(){
    //read again vals 14, 15 and sum
    //calc subtract m_bticks and store result in m_ticks
}

bool ProcMan::operator<(ProcMan& rhs){
    return m_ticks < rhs.m_ticks; 
}

std::string ProcMan::print(){
    //measure all appropraite params based on m_pidDir 

    //format string and return one line of process info
    return "";
}

