#include "../hFiles/agent.h"
#include "../hFiles/agentFactory.h"
#include "../hFiles/eventsHub.h"
#include "../hFiles/agentlifeCicleMng.h"
#include "../hFiles/configurator.h"
#include "../hFiles/configData.h"
#include <cstring>
#include<string>
#include <vector>
extern "C"
{
#include "../logger/inc/logmngr.h"
}


void AgentLifeCycleMng::CreateAgent(const vector<ConfigData>& _config)
{
	Zlog* zlog;
	zlog = ZlogGet("mod2");
	for(vector<ConfigData>::const_iterator it = _config.begin(); it != _config.end(); ++it)
	{
		Agent* agent = 	m_agentFactory->CreateAgent(*it, m_hub);	
		agent->SubscribeToHub();
		m_agents.push_back(agent);
		ZLOG_SEND(zlog, LOG_TRACE, "Agent LCM created agent : %s" , (*it).GetValue("id").c_str());
	}
}

AgentLifeCycleMng::~AgentLifeCycleMng()
{
	delete m_agentFactory;
}

void AgentLifeCycleMng:: JoinAll()
{

	for(vector<Agent*>::const_iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		Agent* agent = *it;
		agent->Join();
	}
}

void AgentLifeCycleMng::DestroyAgents()
{
	for(vector<Agent*>::const_iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		delete *it;
	}
}

void AgentLifeCycleMng::RunAgentsLifeCycleManager(const vector<ConfigData>& _config)
{
	CreateAgent(_config);
}
