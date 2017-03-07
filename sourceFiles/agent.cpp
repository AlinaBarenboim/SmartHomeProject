#include "../hFiles/agent.h"
#include "../hFiles/safeQ.h"
#include "../hFiles/configData.h"
#include "../hFiles/event.h"
#include "../hFiles/eventsHub.h"
#include "../hFiles/tokenizer_t.h"
#include <thread>
#include <unistd.h>
#include <algorithm>
extern "C"
{
#include "../logger/inc/logmngr.h"
}

Agent::Agent(const ConfigData& _conf,  const EventsHub* _hub , bool _isController ):m_agentConfig (_conf.GetAllConfig()) , m_isController(_isController)
{
	m_queue = new SafeQueue<Event*>();
	if (!_hub)
	{
		throw ("events_hub_not_exist");
	}
	else
	{
		m_hub = (EventsHub*)_hub;
	}	
	m_tokenizer = new Tokenezer_t();
	map<string,string>:: iterator it = m_agentConfig.find("config");
	string config = (*it).second;	
	ParseConfigLine(config);
}

void Agent::SubscribeToHub()
{
	if (m_isController)
	{
		m_hub->Subscribe(this);
	}
}



Agent:: ~Agent()
{
	if (m_queue)
	{
		delete m_queue;
		m_queue = 0;
	}
	if (m_tokenizer)
	{
		delete m_tokenizer;
		m_tokenizer = 0;
	}
}

void Agent::ParseConfigLine(const string _config)
{
	m_tokens = m_tokenizer->GetTokensList(_config);
}

void Agent:: ReceiveEvent (const Event* _event)const
{
	m_queue->Push((Event*)_event);
}

Event* Agent::GetNewEvent() 
{

	return m_queue->Pop();
}


void Agent:: SendEvent(const Event& _event)const
{
	(m_hub)->Receive(&_event);
}


void Agent::SendEventToHub(const Event* _event)
{
	m_hub->Receive((Event*)_event);
}

string Agent::GetLocation() const
{
	map<string,string>:: const_iterator iter_room = m_agentConfig.find("room");
	map<string,string>:: const_iterator iter_floor = m_agentConfig.find("floor");
	string location;
	if(iter_floor != m_agentConfig.end())
	{
		location += (*iter_floor).second;
	}
	location += " ";
	if(iter_room != m_agentConfig.end())
	{
		location += (*iter_room).second;
	}
	return location;

}

const string Agent::GetAgentID()const
{
	map<string,string>:: const_iterator iterID = m_agentConfig.find("id");
	string id = (*iterID).second;
	return id;

}

const string Agent::GetAgentConfigLocation()const
{

	return m_subscribeLocation;
}

void Agent::UpdateAgentActionsAndLocation(const string& _action)
{

	Zlog* zlog;
	zlog = ZlogGet("mod1");
	vector<string>:: iterator it = find(m_tokens.begin(), m_tokens.end(), _action);
	if (it != m_tokens.end())
	{
		it++;
		do 
		{
			string event = *it;
			ZLOG_SEND(zlog, LOG_TRACE, "agent interesting in event : %s" , event.c_str());
			m_actionsAndEvents[event] = _action;
		}while (*it++ == "|");
	}
	else
	{
		ZLOG_SEND(zlog, LOG_TRACE, "agent interested in all events: : %s" ,_action.c_str());
		m_actionsAndEvents["all"] = "all";
	}	
	it = find (m_tokens.begin(), m_tokens.end(), "From");
	if (it == m_tokens.end())
	{
		m_subscribeLocation = "all";
	}
	else
	{
		it++;	
		string location = *it;
		m_subscribeLocation = location;
		
	}
}





