#ifndef GENPARSER_H_
#define GENPARSER_H_

//forward declaration
struct Stats;


class Genparser{
public:
    Genparser(int* fd, Stats* stats);
    ~Genparser();

    static void* threadEntry(void* caller);
    void parse();
private:

//
    int* m_fd;
    Stats* m_stats;
};

#endif 
