#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Timer.h"
#include "Reader.h"
#include "StatGen.h"

Timer::Timer(Reader &r, int interval, int count) 
        : m_reader(r), m_intv(interval), m_count(count){
}

Timer::~Timer(){
}

void Timer::start(){
    unsigned int usecs(m_intv*1000); 
    
    for(int i=0;i<m_count;++i){
        m_reader.measure();
        m_reader.read();
       
        std::this_thread::sleep_for(std::chrono::milliseconds(usecs-MEASURE_RES)); 
    }
}
