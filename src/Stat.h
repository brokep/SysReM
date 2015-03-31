#ifndef STAT_H
#define STAT_H

#include <string>

/**
 * Virtual base class for different type of stat measurements.
 * Derived class will define their own measure() and read() methods
 */
class Stat{
public:

    virtual ~Stat(){}
    
    virtual void measure() = 0;
    virtual std::string read() = 0;


};

#endif
