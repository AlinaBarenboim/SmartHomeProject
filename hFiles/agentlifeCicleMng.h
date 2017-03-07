#ifndef __AGENT_LIFE_CICLE_MNG_H__
#define __AGENT_LIFE_CICLE_MNG_H__

class ConfigData;
class AgentFactory;
class Agent;
class EventsHub;

class AgentLifeCycleMng
{
public:
	AgentLifeCycleMng(AgentFactory* _agentFac,EventsHub* _hub) : m_agentFactory((AgentFactory*)_agentFac) , m_hub(_hub){};
	~AgentLifeCycleMng();
	void RunAgentsLifeCycleManager(const vector<ConfigData>& _config);
	void CreateAgent(const vector<ConfigData>& _config);
	void JoinAll();
	void DestroyAgents();
	
protected:
	
private:

	AgentLifeCycleMng(const AgentLifeCycleMng& _agentLCM);
	AgentLifeCycleMng& operator=(const AgentLifeCycleMng&  _agentLCM);
	EventsHub* m_hub;
	AgentFactory* m_agentFactory;
	vector<Agent*> m_agents;
			
};
#endif
