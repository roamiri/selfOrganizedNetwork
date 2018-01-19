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

Manager::Manager(bool start)
{
    std::cout << "Manager started!\n";
}

Manager::~Manager()
{
    false;
}

void Manager::listen_For_Candidacy(const std::string& message)
{
    std::cout << " Candidate received: " << message << std::endl;
}

void Manager::listen_For_ClusterHead(const std::string& message)
{
	std::cout << " Cluster Head received: " << message << std::endl;
}

void Manager::listen_For_Conflict(const std::string& message)
{
	std::cout << " Conflict received: " << message << std::endl;
}
