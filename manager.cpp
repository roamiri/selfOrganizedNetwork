/*
 * Copyright 2018 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "manager.h"
#include <math.h>

Manager::Manager(std::shared_ptr<Painter>p)
:m_draw_thread()
{
	m_painter = p;
    std::cout << "Manager started!\n";
}

Manager::~Manager()
{
	stop_thread = true;
	if(m_draw_thread.joinable()) m_draw_thread.join();
	std::cout << "Deconstruct " << __FILE__ << std::endl;
}

void Manager::listen_For_Candidacy(const candidacy_msg& message)
{
//     std::cout << " Candidate received: xx = " << message.x << ", y=" << message.y << " from id=" << message.id << std::endl;
	bool ib_found = false;
	for(std::vector<mmWaveBS*>::iterator it = m_vector_BSs.begin(); it != m_vector_BSs.end(); ++it) 
	{
		mmWaveBS* mmB = (*it);
		if(euclidean_dist2(message.y, message.y, mmB->getX(), mmB->getY()) <=  pow(in_bound, 2))
			if(mmB->getStatus()==Status::clusterHead)
			{
				ib_found = true;
				joinCluster(message.id, mmB->getClusterID(), Status::inBound);
				break;
			}
			else if((mmB->getStatus()==Status::inBound))
			{
				ib_found = true;
				joinCluster(message.id, mmB->getClusterID(), Status::outBound);
			}
	}
	if(!ib_found)
		makeCluster(message.id);
}

void Manager::listen_For_ClusterHead(const std::string& message)
{
	std::cout << " Cluster Head received: " << message << std::endl;
}

void Manager::listen_For_Conflict(const std::string& message)
{
	std::cout << " Conflict received: " << message << std::endl;
}

void Manager::joinCluster(uint32_t id, uint32_t cluster_id, Status st)
{
	for(std::vector<mmWaveBS*>::iterator it = m_vector_BSs.begin(); it != m_vector_BSs.end(); ++it)
	{
		if((*it)->getID()==id)
		{
			(*it)->setClusterID(cluster_id);
			(*it)->setStatus(st);
			std::shared_ptr<draw_object> new_node = std::make_shared<draw_object>((*it)->getX(), (*it)->getY(), cluster_id);
			m_painter.get()->add_to_draw_queue(new_node);
			m_painter.get()->Enable();
			std::cout << "The BS_" << id << " joined cluster: " << cluster_id << " as " << st << std::endl;
			break;
		}
	}
}

void Manager::makeCluster(uint32_t id)
{
	for(std::vector<mmWaveBS*>::iterator it=m_vector_BSs.begin(); it!=m_vector_BSs.end();++it)
		if((*it)->getID()==id)
		{
			(*it)->setClusterID(id);
			(*it)->setStatus(Status::clusterHead);
			std::shared_ptr<draw_object> new_node = std::make_shared<draw_object>((*it)->getX(), (*it)->getY(), (*it)->getID());
			m_painter.get()->add_to_draw_queue(new_node);
			m_painter.get()->Enable();
			std::cout << "The BS_" << id << " is Cluster Head!!" << std::endl;
			break;
		}
}
