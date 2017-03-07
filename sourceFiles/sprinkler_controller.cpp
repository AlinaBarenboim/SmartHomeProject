#include "../hFiles/sprinkler_controller.h"
#include "../hFiles/eventsHub.h"
#include "../hFiles/agent.h"
#include "../hFiles/event.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <csignal>
extern "C"
{
#include "../logger/inc/logmngr.h"
}

void SprinklerController::Join()
{
	m_sendThread.join();
}

SprinklerController::SprinklerController(const ConfigData& _conf,  const EventsHub* _hub):Agent(_conf,_hub , true)
{
	UpdateAgentActionsAndLocation("On");
	RunAgent();
}

SprinklerController::~SprinklerController() {}


void SprinklerController::RunAgent()
{
	m_sendThread = thread([this] {ProcessEvent() ;});
}


void* SprinklerController:: ProcessEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	while (1)
	{
		Event* newEvent = (Event*)GetNewEvent();
		time_t timer;
  		time ( &timer );
		string location = GetLocation();
		if (newEvent->GetType() == "Fire_Detected")
		{
			Event* ev = new Event(ctime (&timer) ,"Sprinkler Controller Event ", "Sprinkler in action ", location ,"safety");
			SendEventToHub(ev);
			ZLOG_SEND(zlog, LOG_TRACE, "Sprinkler controller sends event to hub: %s" , ev->GetType().c_str());
			//delete ev;
			//ev = 0;
		}
	delete newEvent;
	newEvent = 0;
	}
}




