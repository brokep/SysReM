#ifndef READER_H
#define READER_H

#include <list>
#include <string>

class Stat;

class Reader{
public:
    Reader(std::list<Stat*> &stats, std::string fileName);
    ~Reader();

    void measure();
    void read();

private:
    std::list<Stat*> m_stats;
    std::string m_fileName;

};

#endif
