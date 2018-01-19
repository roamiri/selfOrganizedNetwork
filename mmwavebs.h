#ifndef MMWAVEBS_H
#define MMWAVEBS_H

#include "Signal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/prctl.h>
#include "common.h"

class mmWaveBS{
public:
    /* Explicitly using the default constructor to
     * underline the fact that it does get called */
    mmWaveBS(double x, double y, uint32_t id, Status st=idle) : the_thread() { m_xx =x; m_yy =y; m_id =id; m_status = st;}
    ~mmWaveBS()
    {
        stop_thread = true;
        if(the_thread.joinable()) the_thread.join();
    }
    void Start();
	
    void setClusterID(int id) {cluster_id = id;}
    uint32_t getClusterID() {return cluster_id;}
    
    uint32_t getID(){return m_id;}
    
    double getX(){return m_xx;}
    double getY(){return m_yy;}
    
    Status getStatus(){return m_status;}
    void setStatus(Status st){m_status = st;}
    
    Signal<candidacy_msg const &> candidacy;
    Signal<std::string const &> clusterHead;
    Signal<std::string const &> conflict;

    void listen(std::string const &message);
    
private:
    std::thread the_thread;
	bool stop_thread = false;
    void ThreadMain();
    
	uint32_t m_id;
    uint32_t cluster_id = -1;
    double m_xx;
    double m_yy;
	Status m_status;
	
	timer_t T;
};


#endif // MMWAVEBS_H
