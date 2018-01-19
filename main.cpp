#include "Signal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/prctl.h>

#include "manager.h"
#include "mmwavebs.h"
#include "idgenerator.h"


int main() {
    
  Manager manager(true);
  IDGenerator* _idGenerator = IDGenerator::instance();
  
  for(int i =0;i<16;i++)
  {
	mmWaveBS* BS = new mmWaveBS(3.0*i , 3.0*i, _idGenerator->next());
	manager.vector_BSs.push_back(BS);
	BS->Start();
	BS->candidacy.connect_member(&manager, &Manager::listen_For_Candidacy);
	BS->clusterHead.connect_member(&manager, &Manager::listen_For_ClusterHead);
	BS->conflict.connect_member(&manager, &Manager::listen_For_Conflict);
  }
 
  while(1){true;}
  return 0;
}
