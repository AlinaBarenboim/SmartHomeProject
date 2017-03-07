#include "../hFiles/agentCreator.h"
#include "../hFiles/agentFactory.h"
#include "../hFiles/configData.h"
#include <map>
#include <iostream>
using namespace std;
	
AgentFactory::AgentFactory() {}

AgentFactory::~AgentFactory(){}

AgentFactory& AgentFactory::GetInstance() 
{ 
	static AgentFactory agentFactory; 
	return agentFactory; 
}	

void AgentFactory::AddCreator(const string& _name, const AgentCreator* _creator)
{
	m_creators[_name] = (AgentCreator*)_creator;
}

Agent* AgentFactory::CreateAgent(const ConfigData& _conf, const EventsHub* _hub) const
{
	map<string, AgentCreator*>::const_iterator it = m_creators.find(_conf.GetValue("type"));
	if(it != m_creators.end())
	{
		return (it->second)->CreateAgent(_conf, _hub);
	}
	else
	{
		return 0;
	}
}	


