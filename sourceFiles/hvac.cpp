#include "../hFiles/agent.h"
#include "../hFiles/event.h"
#include "../hFiles/hvac.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
extern "C"
{
#include "../logger/inc/logmngr.h"
}

HVAC::HVAC(const ConfigData& _conf,  const EventsHub* _hub) : Agent(_conf,_hub,true)
{
	UpdateAgentActionsAndLocation("shutdown");
	RunAgent();
}

void HVAC:: Join()
{
	m_receiveThread.join();
}

HVAC::~HVAC(){} 

void HVAC::RunAgent()
{
	m_receiveThread = thread([this] {ProcessEvent();});
}

void* HVAC:: ProcessEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	while (1)
	{

		Event* newEvent = (Event*)GetNewEvent();
		time_t timer;
		string location = GetLocation();
		if (newEvent->GetType() == "ambient_temp" || newEvent->GetType() == "ROOM_EMPTY")
		{
			Event* shutdownEvent = new Event(ctime (&timer),"HVAC_action", "HVAC Shut down", location ,"safety");
			SendEventToHub(shutdownEvent);
			ZLOG_SEND(zlog, LOG_TRACE, "HVAC send event to hub: %s" , shutdownEvent->GetType().c_str());

		}
	delete newEvent;

	
	}
}



