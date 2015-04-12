#ifndef PROCMAN_H
#define PROCMAN_H

#include <string>

/**
 * Manager of the processes
 */
class ProcMan{
public:
    //creat ProcMan with path to process /proc/[pid]
    ProcMan(std::string pidDir);

    //read values before the wait
    void readBefore();
    //read the values after the wait and calulate delta
    void readAfter();
    
    //for sorting, sort on m_ticks
    bool operator<(ProcMan& rhs);

    //return formatted per procces line og info about process
    std::string print();


private:
    std::string m_pidDir;
    int m_bticks;
    int m_ticks;
};

#endif
