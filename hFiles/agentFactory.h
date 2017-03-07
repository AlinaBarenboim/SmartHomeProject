#ifndef __AGENT_FACTORY_H__
#define __AGENT_FACTORY__H__
#include <map>
#include <string>
using namespace std;
class EventsHub;
class AgentCreator;
class Agent;
class ConfigData;
class Application;

class AgentFactory
{
	friend Application;
public:
	~AgentFactory();
	static AgentFactory& GetInstance();
	Agent* CreateAgent(const ConfigData& _conf, const EventsHub* _hub) const;	
	void AddCreator(const string& _name, const AgentCreator* _creator);

private:
	AgentFactory();
	AgentFactory(const AgentFactory& _fact);
	void operator=(const AgentFactory& _fact);
	map<string, AgentCreator*> m_creators;
};

#endif

