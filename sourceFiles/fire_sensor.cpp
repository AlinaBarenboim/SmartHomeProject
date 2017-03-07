#include "../hFiles/fire_sensor.h"
#include "../hFiles/agent.h"
#include "../hFiles/event.h"
#include "../hFiles/eventsHub.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <csignal>
extern "C"
{
#include "../logger/inc/logmngr.h"
}

FireDetector* FireDetector::m_fireDetector = 0; 

void FireDetector::Join()
{
	m_sendThread.join();

}

FireDetector::FireDetector(const ConfigData& _conf,  const EventsHub* _hub) : Agent(_conf,_hub ,false)
{
	UpdateAgentActionsAndLocation("action");
	RunAgent();
}

FireDetector::~FireDetector() {}

void SignalHandlerFunc(int signum)
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	if (signum == SIGUSR2)
	{
		FireDetector::GenerateEvent();
		ZLOG_SEND(zlog, LOG_TRACE, "new signal detected : %d" , signum);
	}    
}



void FireDetector::RunAgent()
{
	m_sendThread = thread([this] {WaitForEvent() ;});
}

void* FireDetector::WaitForEvent()
{
	while(1)
	{
		if(!m_fireDetector)
		{
			signal (SIGUSR2, SignalHandlerFunc);
			m_fireDetector = this;
		}
	}	
}


void FireDetector:: GenerateEvent() //static function. 
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	time_t timer;
	time(&timer);
	string location = m_fireDetector->GetLocation();
	stringstream buff;
	buff<<  "Fire Detected from fire detector "<< endl;
	Event* fireEvent = new Event(ctime (&timer),"Fire_Detected", buff.str(), location , "safety");
	m_fireDetector->SendEventToHub(fireEvent);
	ZLOG_SEND(zlog, LOG_TRACE, "Fire detector send event to hub after receiving sigusr2 signal: %s" , fireEvent->GetType().c_str());
	signal (SIGINT, SignalHandlerFunc);
}


