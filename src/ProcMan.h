#ifndef PROCMAN_H
#define PROCMAN_H

#include <string>

/**
 * Manager of each individual  process
 */
class ProcMan{
public:
    //creat ProcMan with path to process /proc/[pid]
    ProcMan(int pidDir);

    //read values before the wait
    void readBefore();
    //read the values after the wait and calulate delta
    void readAfter();
    
    //for sorting, sort on m_ticks
    bool operator<(ProcMan& rhs);

    //return formatted per procces line og info about process
    std::string print();


private:
    int m_pidDir;
    int m_bticks;
    int m_ticks;
    int cpu_ticks;
};

#endif
