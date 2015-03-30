#ifndef READER_H
#define READER_H

#include <list>

class Stat;

class Reader{
public:
    Reader(std::list<Stat*> &stats);
    ~Reader();

    void measure();
    void read();

private:
    std::list<Stat*> m_stats;

};

#endif
