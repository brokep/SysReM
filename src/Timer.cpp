
#include "Timer.h"
#include "Reader.h"

Timer::Timer(Reader &r, int interval, int count) 
        : m_reader(r), m_intv(interval), m_count(count){
}

Timer::~Timer(){
}

void Timer::start(){
    //call measure on r
    //call read on r 
    //wait for intv 
    //repeat count times
}
