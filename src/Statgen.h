#ifndef STATGEN_H_
#define STATGEN_H_

class Statgen{
public:
    Statgen(int* fd, int interval, int count);
    ~Statgen();

    void start();

private:
    int* m_fd;
    int m_interval;
    int m_count;

};

#endif 
