
#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <thread>
#include "common.h"
#include "mmwavebs.h"
#include <memory>
#include "painter.h"

class Manager
{
    public:
        
        Manager(std::shared_ptr<Painter> p);
        ~Manager();
        
		void listen_For_Candidacy(candidacy_msg const &message);
		void listen_For_ClusterHead(std::string const &message);
		void listen_For_Conflict(std::string const &message);
		void joinCluster(uint32_t id, uint32_t cluster_id, Status st);
		void makeCluster(uint32_t id);
		
        std::vector<mmWaveBS*> m_vector_BSs;
		
private:
	std::shared_ptr<Painter> m_painter;
	bool stop_thread = false;
	std::thread m_draw_thread;
};

#endif // MANAGER_H
