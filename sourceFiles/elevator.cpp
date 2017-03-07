#include "../hFiles/elevator.h"
#include "../hFiles/agent.h"
#include "../hFiles/event.h"
#include "../hFiles/eventsHub.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
extern "C"
{
#include "../logger/inc/logmngr.h"
}
const int FloorInitialition = 5;

Elevator::Elevator(const ConfigData& _conf,  const EventsHub* _hub): Agent(_conf,_hub ,true)
{
	m_currFloor = FloorInitialition;
	UpdateAgentActionsAndLocation("elevator_down");
	RunAgent();
}

void Elevator::Join()
{
	m_receiveThread.join();
	m_sendThread.join();
}


Elevator::~Elevator(){}

void Elevator::RunAgent()
{
	m_sendThread = thread([this] {GenerateEvent() ;});
	m_receiveThread = thread([this] {ProcessEvent();});
}

void* Elevator:: ProcessEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	while (1)
	{
		Event* newEvent = (Event*)GetNewEvent();
		ZLOG_SEND(zlog, LOG_TRACE, "elevator received event : %s" , newEvent->GetType().c_str());
		time_t timer;
  		time ( &timer );
		string location = GetLocation();
		if (newEvent->GetType() == "Fire_Detected")
		{
			Event* elevDownEvent = new Event(ctime (&timer) ,"Elevator_action", " Elevator_down", location ,"safety");
			SendEventToHub(elevDownEvent);
			ZLOG_SEND(zlog, LOG_TRACE, "elevator send event to hub : %s" , elevDownEvent->GetType().c_str());
			//delete elevDownEvent;
		}
	delete newEvent;
	newEvent = 0;
	}
}


void* Elevator:: GenerateEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	time_t timer;
	time(&timer);
	while (1)
	{
		m_currFloor = m_currFloor + (rand() % 8 -4);
		string location = GetLocation();
		stringstream loc;
		loc << "Floor number " << location << endl;
		stringstream buff;
		buff<<  " Elevator opens at floor : " << m_currFloor << endl;
		Event* floorChangeEvent = new Event(ctime(&timer),"Elevator_action", buff.str(),"all" ,"Elevator_action");
		SendEventToHub(floorChangeEvent);
		sleep(20);
		ZLOG_SEND(zlog, LOG_TRACE, "elevator send event to hub : %s" , floorChangeEvent->GetType().c_str());

	}
}

