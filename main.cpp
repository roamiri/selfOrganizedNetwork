#include "Signal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/prctl.h>

#include "manager.h"
#include "mmwavebs.h"

int main() {
    
  Manager manager(true);
  
  
//   mmWaveBS BS(3.0 , 3.0);
//   BS.candidacy.connect( &Manager::listen);
  
  mmWaveBS* BS1 = new mmWaveBS(3.0 , 3.0, 0);
  BS1->Start();
//   BS1->setClusterID(0);
  BS1->candidacy.connect_member(&manager, &Manager::listen);
  
  mmWaveBS* BS2 = new mmWaveBS(3.0 , 4.0, 1);
  BS2->Start();
//   BS2->candidacy.connect_member(BS1, &mmWaveBS::listen);
  mmWaveBS* BS3 = new mmWaveBS(3.0 , 10.0, 2);
  BS3->Start();
  BS3->setClusterID(2);
  manager.vector_BSs.push_back(BS1);
  manager.vector_BSs.push_back(BS2);
  manager.vector_BSs.push_back(BS3);
 
  while(1){true;}
  return 0;
}
