#ifndef MMWAVEBS_H
#define MMWAVEBS_H

#include "Signal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/prctl.h>

class mmWaveBS{
public:
    /* Explicitly using the default constructor to
     * underline the fact that it does get called */
    mmWaveBS(double x, double y, uint32_t id) : the_thread() { xx =x; yy =y; m_id =id;}
    ~mmWaveBS()
    {
        stop_thread = true;
        if(the_thread.joinable()) the_thread.join();
    }
    void Start();
    void setClusterID(int id) {cluster_id = id;}
    
    int getClusterID() {return cluster_id;}
    
    Signal<std::string const &> candidacy;
    Signal<std::string const &> clusterHead;
    Signal<std::string const &> conflict;

    void listen(std::string const &message);
    
private:
    std::thread the_thread;
    bool stop_thread = false;
    uint32_t m_id;
    int cluster_id = -1;
    double xx;
    double yy;
    void ThreadMain();
};


#endif // MMWAVEBS_H
