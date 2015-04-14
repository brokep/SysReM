#ifndef DEVMAN_H
#define DEVMAN_H

#include <string>

//class used to hadle disk "sd" devices as used in DiskStat
class DevMan{
public:
    //name of the device, and position in /proc/diskstats
    DevMan(std::string devName, int pos);
    ~DevMan();

    void readBefore();
    void readAfter();

    std::string print();

private:
    std::string m_devName;
    int m_pos;

    //uitl vals, prev in [0], after in [1] 
    int reads[2];
    int sectors_read[2];
    int writes[2];
    int sectors_writ[2];

};

#endif
