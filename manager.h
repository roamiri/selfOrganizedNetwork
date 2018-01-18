
#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "mmwavebs.h"

class Manager
{
    public:
        
        Manager(bool start);
        ~Manager();
        void listen(std::string const &message);
        std::vector<mmWaveBS*> vector_BSs;
};

#endif // MANAGER_H
