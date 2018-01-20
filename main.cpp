#include "Signal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/prctl.h>
#include <memory>

#include "manager.h"
#include "mmwavebs.h"
#include "idgenerator.h"
#include "painter.h"
#include "ppunfix5.h"

int main() {
    
  IDGenerator* _idGenerator = IDGenerator::instance();
  Manager manager;
  std::shared_ptr<Painter> _painter = std::make_shared<Painter>(manager.m_vector_BSs);
  _painter.get()->Start();
  
  
  double dummy = 1;
  int num_nodes = 100;
  double beta = 300, gamma = 0.1, r = 0.05;

  straussprocess* p2;
  p2  = new straussprocess(2,dummy,gamma,r,num_nodes);   // dummy is dummy
  p2-> makeprocess(50000);
  p2->saveData("data.dat");
//   double theta = 100.0;
//   p2-> transform(0,theta);
  
//   	mmWaveBS* BS = new mmWaveBS(100.0 *p2->data[0].pt[0] , 100.0 *p2->data[0].pt[1], _idGenerator->next());
// 	BS->setClusterID(BS->getID());
// 	BS->setStatus(Status::clusterHead);
// 	manager.m_vector_BSs.push_back(BS);
// 	BS->Start();
// 	BS->candidacy.connect_member(&manager, &Manager::listen_For_Candidacy);
// 	BS->clusterHead.connect_member(&manager, &Manager::listen_For_ClusterHead);
// 	BS->conflict.connect_member(&manager, &Manager::listen_For_Conflict);
//   
	for(int i =1;i<num_nodes;i++)
	{
		std::shared_ptr<mmWaveBS> BS = std::make_shared<mmWaveBS>(100.0 *p2->data[i].pt[0] , 100.0 *p2->data[i].pt[1], _idGenerator->next());
		BS.get()->setColor(0);
		manager.m_vector_BSs.push_back(BS);
		BS->Start();
		BS->candidacy.connect_member(&manager, &Manager::listen_For_Candidacy);
		BS->clusterHead.connect_member(&manager, &Manager::listen_For_ClusterHead);
		BS->conflict.connect_member(&manager, &Manager::listen_For_Conflict);
	}
	
	
	while(1)
	{
		true;
	}
  return 0;
}
