#include "../hFiles/safeQ.h"
#include "../hFiles/eventsHub.h"
#include "../hFiles/event.h"
#include "../hFiles/agent.h"
#include <algorithm>
#include <unistd.h>
#include <thread>
#include <string>
extern "C"
{
#include "../logger/inc/logmngr.h"
}

EventsHub::EventsHub()
{
	 m_receiveQueue = new SafeQueue<Event*>();	 
}

EventsHub::~EventsHub()
{
	if (m_receiveQueue)
	{
		delete m_receiveQueue;
		m_receiveQueue = 0;
	}
}

void EventsHub::EventHubRun()
{
	m_receiveThread = thread([this] {ProcessEvent();});
}


void EventsHub::Subscribe (const Agent* _agent)
{
	m_subscribers.InsertSubscriber(_agent);
}


void EventsHub::Receive(const Event* _event)
{
	m_receiveQueue->Push((Event*)_event);
}


void EventsHub::Publish(const Event* _event)
{
	const vector<Agent*>& publishVec =  m_subscribers.GetRelevantSubscriber(_event);
	Zlog* zlog;
	zlog = ZlogGet("mod2");
	if (publishVec.empty())	
	{
		ZLOG_SEND(zlog, LOG_TRACE, "Events hub received empty vector of agents. no one intersted in:%s" , _event->GetType().c_str());
		return;
	}
	
	ZLOG_SEND(zlog, LOG_TRACE, "Events hub received vector of agents who interested in:%s" , _event->GetType().c_str());	
	vector<Agent*>:: const_iterator m_it = publishVec.begin();
	for(m_it = publishVec.begin() ; m_it != publishVec.end() ; ++m_it)
	{
		ZLOG_SEND(zlog, LOG_TRACE, "Events hub sending event to agents who interested in:%s" , _event->GetType().c_str());	
		(*m_it)->ReceiveEvent(new Event(*_event));

	}
	delete _event;
}	

void EventsHub::ProcessEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	while(1)
	{
		Event* event = m_receiveQueue->Pop();
		ZLOG_SEND(zlog, LOG_TRACE, "Received event in event hub:  %s" , event->GetType().c_str());
		Publish(event);
	}	
}


vector <Agent*>& EventsHub::SubscribeData:: GetIntersection(const string& _event, const string& _location)
{
	Zlog* zlog;
	zlog = ZlogGet("mod2");
	m_relevantReturnedAgents.clear();
	map<string,vector<Agent*>>:: iterator eventIter; //finds relevant event
	map<string,vector<Agent*>>:: iterator locationIter;//finds relevant location
	
	eventIter = m_events.find("all"); //find agents who want to get all events
	if (eventIter != m_events.end())
	{
		m_relevantReturnedAgents = (*eventIter).second;
		ZLOG_SEND(zlog, LOG_TRACE, "Agents that interested in all events inserted to relevant agents vector,  %s" , (*eventIter).first.c_str());
	
	}
	eventIter = m_events.find(_event); //searching in events map

	locationIter = m_locations.find(_location); //searching in locations map

	if (eventIter == m_events.end())
	
	{
		ZLOG_SEND(zlog, LOG_TRACE, "There is no Agents who interested in events %s. Vector with agents who interested in all events / empty vector returned."  , _event.c_str());
		return m_relevantReturnedAgents;
	}
	m_relevantReturnedAgents = CheckIfIntersected ((*eventIter).second, (*locationIter).second);
	return m_relevantReturnedAgents;
}


vector<Agent*>& EventsHub::SubscribeData::CheckIfIntersected (vector<Agent*> _events, vector<Agent*> _locations)
{
	
	Zlog* zlog;
	zlog = ZlogGet("mod2");
	vector<Agent*>:: iterator itEv = _events.begin();
	vector<Agent*>:: iterator itLoc;

	for (itEv; itEv != _events.end() ; ++itEv)
	{
		Agent* agent = *itEv;
		ZLOG_SEND(zlog, LOG_TRACE, "Agent to check intersection: %s" , agent->GetID().c_str());

		itLoc = find(_locations.begin(), _locations.end(), agent);
		
  		if (itLoc == _locations.end())
  		{
  			map<string,vector<Agent*>>:: iterator it = m_locations.find("all");
  			if (it != m_locations.end())
  			{
  				vector<Agent*> allVec = (*it).second;
  				vector<Agent*>:: iterator itAll ;
  				itAll = find(allVec.begin(), allVec.end(), agent);
  				if (itAll != allVec.end())
  				{
  					m_relevantReturnedAgents.push_back(agent);
  					ZLOG_SEND(zlog, LOG_TRACE, "Agent  %s found intersection in all location" , agent->GetID().c_str())
  				}
  				else
  				{
  					ZLOG_SEND(zlog, LOG_TRACE, "Agent  %s not found in location vector. No intersection!" , agent->GetID().c_str());

  				
  				}
  			}
  			
  		}
  		else
  		{
  			ZLOG_SEND(zlog, LOG_TRACE, "Agent  %s  found in location vector. Intersection! Inserted to relevant agents vector" , agent->GetID().c_str());
  			m_relevantReturnedAgents.push_back(agent);
  		}

	}
	return m_relevantReturnedAgents;

}



const vector<Agent*>& EventsHub::SubscribeData::GetRelevantSubscriber(const Event* _event)
{
	string event = _event->GetType();
	string location = _event->GetLocation();
	return GetIntersection(event,location);
	
}

void EventsHub::SubscribeData::InsertSubscriber (const Agent* _agent)
{
	Zlog* zlog;
	zlog = ZlogGet("mod2");
	string location = _agent->GetAgentConfigLocation();
	ZLOG_SEND(zlog, LOG_TRACE, "Agent: %s interested in evens from %s" , _agent->GetID().c_str(), location.c_str());
	map<string,vector<Agent*>>:: iterator iter;
	map<string,string> events = _agent->GetAgentConfigurationEvents();
	map<string,string>:: iterator eventIt;
	for (eventIt = events.begin(); eventIt != events.end(); ++eventIt )
	{
		string nextEvent = (*eventIt).first;
		ZLOG_SEND(zlog, LOG_TRACE, "Agent: %s interested in next event: %s" , _agent->GetID().c_str(), nextEvent.c_str());
		iter = m_events.find(nextEvent);
		if (iter == m_events.end())
		{
			vector<Agent*> newAgent;
			newAgent.push_back((Agent*)_agent);
			m_events[nextEvent] = newAgent;
			ZLOG_SEND(zlog, LOG_TRACE, "New event inserted to subscribers events map: %s" , nextEvent.c_str());
		}
		else
		{
			(*iter).second.push_back((Agent*)_agent);
			ZLOG_SEND(zlog, LOG_TRACE, "Following event is already exist in map , agent added to existing map: %s" , nextEvent.c_str());
		}
	}

	iter = m_locations.find(location);
	if (iter == m_locations.end())
	{
		vector<Agent*> newAgent;
		newAgent.push_back((Agent*)_agent);
		m_locations[location] = newAgent;
		ZLOG_SEND(zlog, LOG_TRACE, "New location inserted to subscribers events map: %s" ,location.c_str());
	}
	else
	{
		(*iter).second.push_back((Agent*)_agent);
		ZLOG_SEND(zlog, LOG_TRACE, "Location exist, agent added to existing map: %s" ,location.c_str());
	}
	m_numOfSubscribers++;
}

