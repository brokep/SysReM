#include <unistd.h>
#include "JiffyTimer.h"

JiffyTimer::JiffyTimer(int mswait) : m_mswait(mswait){
}

JiffyTimer::~JiffyTimer(){
}

void JiffyTimer::wait(){
    usleep(m_mswait*1000); 
}

int JiffyTimer::getExpectedTicks(){
    return m_mswait/1000.0*sysconf(_SC_CLK_TCK);
}
