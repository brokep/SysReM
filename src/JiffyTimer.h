#ifndef JIFFYTIMER_H
#define JIFFYTIMER_H


class JiffyTimer{
public:
    JiffyTimer(int mswait);
    ~JiffyTimer();

    void wait();
    int getExpectedTicks();
private:
    int m_mswait;
};

#endif
