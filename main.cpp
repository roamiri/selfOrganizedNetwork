#include "Signal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/prctl.h>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

#include "manager.h"
#include "mmwavebs.h"
#include "idgenerator.h"
#include "painter.h"
#include "ppunfix5.h"

int main() 
{
	bool create_output = true;
  IDGenerator* _idGenerator = IDGenerator::instance();
  Manager manager;
  std::shared_ptr<Painter> _painter = std::make_shared<Painter>(manager.m_vector_BSs);
  _painter.get()->Start();
  
  int num_nodes = 124;
  
  
  // MAke a ... distribution of points
//   double dummy = 1;
//   double beta = 300, gamma = 0.1, r = 0.05;
// 
//   straussprocess* p2;
//   p2  = new straussprocess(2,dummy,gamma,r,num_nodes);   // dummy is dummy
//   p2-> makeprocess(50000);
//   p2->saveData("data.dat");

  // Read a file from matlab to simulate poisson point process
	double data[num_nodes][2];
	std::fstream _file("../mfiles/exptable.txt");
	int i =0;
	if(_file.fail())
		std::cerr << "input data file does not exis!" << std::endl;
	while(_file)
	{
		int j=0;
		std::string line;
		std::getline(_file, line);
		std::istringstream is(line);
		double num;
		while(is >> num)
		{
			data[i][j] = num;
			j++;
		}
		i++;
	}
  
  //   
	for(int i =0;i<num_nodes;i++)
	{
		if(data[i][0]!=NULL)
		{
	// 		std::shared_ptr<mmWaveBS> BS = std::make_shared<mmWaveBS>(100.0 *p2->data[i].pt[0] , 100.0 *p2->data[i].pt[1], _idGenerator->next());
			std::shared_ptr<mmWaveBS> BS = std::make_shared<mmWaveBS>(1000.0 *data[i][0], 1000.0 *data[i][1], _idGenerator->next());
			BS.get()->setColor(0);
			manager.m_vector_BSs.push_back(BS);
			BS.get()->Start();
			BS.get()->candidacy.connect_member(&manager, &Manager::listen_For_Candidacy);
			BS.get()->clusterHead.connect_member(&manager, &Manager::listen_For_ClusterHead);
			BS.get()->conflict.connect_member(&manager, &Manager::listen_For_Conflict);
		}
	}
	
	
// 	while(1)
	{
		std::this_thread::sleep_for( std::chrono::seconds(10) );
		_painter.get()->Enable();
	}
	
	std::ofstream output_file("clusters.csv");
	if(create_output)
	{
		for(std::vector<std::shared_ptr<mmWaveBS>>::iterator it=manager.m_vector_BSs.begin(); it!=manager.m_vector_BSs.end();++it)
		{
			std::shared_ptr<mmWaveBS> mmB = (*it);
			if(mmB.get()->getStatus()==Status::clusterHead)
			{
				uint32_t cid = mmB.get()->getClusterID();
				output_file << mmB.get()->getX() << "," << mmB.get()->getY() << ",";
				for(std::vector<std::shared_ptr<mmWaveBS>>::iterator it2=manager.m_vector_BSs.begin(); it2!=manager.m_vector_BSs.end();++it2)
				{
					std::shared_ptr<mmWaveBS> mmB2 = (*it2);
					if(mmB2.get()->getClusterID() == cid)
					{
						output_file << mmB2.get()->getX() << "," << mmB2.get()->getY() << ",";
					}
				}
				output_file << std::endl;
			}
		}
	}
	
	return 0;
}
