#ifndef TIMER_H
#define TIMER_H

class Reader;

class Timer{
public:
    Timer(Reader &r, int interval, int count);
    ~Timer();

    void start();    



private:
    Reader &m_reader; 
    int m_intv;
    int m_count;

};

#endif
