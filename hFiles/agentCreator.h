#ifndef __AGENT_CREATOR_H__
#define __AGENT_CREATOR__H__

class ConfigData;
class EventsHub;
class Agent;
class AgentCreator
{
public:
	AgentCreator(){}
	virtual ~AgentCreator() = 0 ;	
	virtual Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub){};
		
protected:
	
private:
	AgentCreator(const AgentCreator& _agentCreator);
	AgentCreator& operator=(const AgentCreator& _agentCreator);
};
#endif
