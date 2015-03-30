#ifndef STAT_H
#define STAT_H

#include <string>

class Stat{
public:

    virtual ~Stat(){}
    
    virtual void measure() = 0;
    virtual std::string read() = 0;


};

#endif
