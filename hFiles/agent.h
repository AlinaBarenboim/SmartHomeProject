#ifndef __AGENT_H__
#define __AGENT_H__
#include <thread>
#include <iostream>
#include <string>
#include <map>
#include <vector>
class ConfigData;
template <typename T>
class SafeQueue;
class EventsHub;
class Tokenezer_t;
class Event;
using namespace std;

class Agent
{
	friend class EventsHub;

public:
	Agent(const ConfigData& _conf, const EventsHub* _hub, bool _isController);
	virtual ~Agent() = 0;
	virtual void Join() = 0;
	void ReceiveEvent (const Event* _event) const ;
	void  SubscribeToHub();
		
	const string GetAgentID() const;
	const string GetAgentConfigLocation() const;
	//const string GetAgentConfigEvent() const;
	const map<string,string>& GetAgentConfigurationEvents() const {return m_actionsAndEvents;}
	
	const string& GetType() const {map<string,string>::const_iterator it = m_agentConfig.find("type"); return (*it).second;}
	const string& GetID() const {map<string,string>:: const_iterator it = m_agentConfig.find("id");return (*it).second;}
	const string& GetRoom() const {map<string,string>:: const_iterator it = m_agentConfig.find("room"); return (*it).second;}
	const string& GetFloor() const {map<string,string>:: const_iterator it = m_agentConfig.find("floor"); return (*it).second;}
	const string& GetLog() const {map<string,string>:: const_iterator it = m_agentConfig.find("log"); return (*it).second;}
	const string& GetConfig() const {map<string,string>:: const_iterator it = m_agentConfig.find("config");return (*it).second;}
		
protected:

	Event* GetNewEvent() ;
	const EventsHub* GetHub() const;
	virtual string GetLocation() const;
	void SendEventToHub(const Event* _event);
	void UpdateAgentActionsAndLocation(const string& _action);	
private:
	Agent(const Agent& _agent);
	Agent& operator=(const Agent& _agent);
	void SendEvent(const Event& _event)const;
	void SetAgentSubscribeConfiguration();
	void ParseConfigLine(const string _config);
	virtual void RunAgent() = 0;
	
	
	SafeQueue <Event*>* m_queue;
	map<string,string> m_agentConfig;
	string m_subscribeLocation;
	EventsHub* m_hub;	
	Tokenezer_t* m_tokenizer;	
	map<string,string> m_actionsAndEvents;
	vector<string> m_tokens;
	bool m_isController;

			
};
#endif


