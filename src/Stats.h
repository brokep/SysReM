#ifndef STATS_H_
#define STATS_H_


struct Stats{
    //gen cpu stats
    double user;
    double nice;
    double system;
    double iowait;
    double steal;
    double idle; 

    //etc..

};

#endif 
