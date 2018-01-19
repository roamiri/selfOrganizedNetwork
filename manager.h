
#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "common.h"
#include "mmwavebs.h"

class Manager
{
    public:
        
        Manager(bool start);
        ~Manager();
        
		void listen_For_Candidacy(candidacy_msg const &message);
		void listen_For_ClusterHead(std::string const &message);
		void listen_For_Conflict(std::string const &message);
		void joinCluster(uint32_t id, uint32_t cluster_id, Status st);
		void makeCluster(uint32_t id);
		
        std::vector<mmWaveBS*> m_vector_BSs;
};

#endif // MANAGER_H
