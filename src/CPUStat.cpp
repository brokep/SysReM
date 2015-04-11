#include <fstream>
#include <numeric>
#include <unistd.h>
#include "CPUStat.h"
#include "StatGen.h"



CPUStat::CPUStat(){
}

CPUStat::~CPUStat(){
}


void CPUStat::measure(){
    //cpu specific measurements 
    using std::ifstream;
    ifstream in("/proc/stat");
    char ch[3];
    in>>ch;
    int b[7]; //before
    int a[7]; //after
    int totalTicks;


    in>>b[0];//user;
    in>>b[1];//nice;
    in>>b[2];//system;
    in>>b[3];//idle;
    in>>b[4];//iowait
    in>>b[5];
    in>>b[6];

    usleep(1000*MEASURE_RES);

    in.seekg(0);
    in>>ch;
    in>>a[0];//user;
    in>>a[1];//nice;
    in>>a[2];//system;
    in>>a[3];//idle;
    in>>a[4];//iowait
    in>>a[5];
    in>>a[6];
       
    totalTicks = std::accumulate(a, a+7, 0) - std::accumulate(b, b+7, 0);

    m_user = 100.0*(a[0] - b[0])/totalTicks;
    m_nice = 100.0*(a[1] - b[1])/totalTicks;
    m_system = 100.0*(a[2] - b[2])/totalTicks;
    m_idle = 100.0*(a[3] - b[3])/totalTicks;
    m_iowait = 100.0*(a[4] - b[4])/totalTicks;

}

std::string CPUStat::read(){
    char buf[1000];
    char buf1[100];
    char a[200];
    sprintf(buf1, "CPU Utilization %cuser\t%cnice\t%csystem\t%ciowait\t%cidle\n", '%', '%', '%', '%', '%'); 
    sprintf(buf, "\t\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f \n", m_user, m_nice, m_system, m_iowait, m_idle); 
    sprintf(a, "%s%s", buf1, buf);
    return a;
}
