#ifndef __EVENTS_HUB_H__
#define __EVENTS_HUB_H__
class Agent;
class Event;
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include<thread>
template <typename T>
class SafeQueue;
class SubscribeData;
using namespace std;


class EventsHub
{
	friend class Agent;
private:
	class SubscribeData
	{
	public:
		SubscribeData() :m_numOfSubscribers(0){};
		~SubscribeData(){};
		void InsertSubscriber (const Agent* _agent);
		const vector<Agent*>& GetRelevantSubscriber(const Event* _event);
		int GetNumOfSubscribers()const {return m_numOfSubscribers;}
		vector <Agent*>&  GetIntersection(const string& _event, const string& _location);
		vector<Agent*>& CheckIfIntersected (vector<Agent*> _events, vector<Agent*> _locations);
		
	protected:
	private:

		vector<Agent*> m_subData;
		int m_numOfSubscribers;
		vector <Agent*> m_relevantReturnedAgents;		 
		map<string,vector<Agent*>> m_events;
		map<string,vector<Agent*>> m_locations;
	
	};
	

public:
	EventsHub();
	~EventsHub();
	void EventHubRun();
	void Subscribe (const Agent* _agent);
	void Receive(const Event* _event);
	void Join(){m_receiveThread.join();}
	
protected:
	
private:

	void Publish(const Event* _event);
	void ProcessEvent();
	EventsHub(const EventsHub& _hub);
	EventsHub& operator=(const EventsHub& _hub);
	
	thread m_receiveThread;
	SafeQueue <Event*>* m_receiveQueue;
	SubscribeData m_subscribers;
		
};
#endif
