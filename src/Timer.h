#ifndef TIMER_H
#define TIMER_H

class Reader;

class Timer{
public:
    Timer(Reader &r, int interval, int count);
    ~Timer();

    void start();    



private:
    Reader &m_reader __attribute__((unused)); 
    int m_intv __attribute__((unused));
    int m_count __attribute__((unused)); //suppress warning until implemetatino

};

#endif
