#include "../hFiles/temp_sensor.h"
#include "../hFiles/agent.h"
#include "../hFiles/event.h"
#include "../hFiles/eventsHub.h"
#include <ctime>
#include <thread>
#include <unistd.h>
#include <iomanip>
#include <string>
#include <cstring>
extern "C"
{
#include "../logger/inc/logmngr.h"
}


TempSensor::TempSensor(const ConfigData& _conf,  const EventsHub* _hub):Agent(_conf,_hub ,false)
{
	RunAgent();
}

TempSensor::~TempSensor() {}

void TempSensor:: Join()
{
	m_sendThread.join();
}

void TempSensor:: RunAgent()
{

	m_sendThread = thread([this] {GenerateEvent();});

}

void TempSensor:: Wait( int seconds)const 
{ 
  clock_t endwait; 
  endwait = clock () + seconds * CLOCKS_PER_SEC; 
  while (clock() < endwait) {} 
} 
 
void TempSensor:: GenerateEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	while (1) 
	{
		time_t timer;
		time(&timer);
		int  temp = (rand() % 61 - 5);
		stringstream buff;
		buff<<  " Current temperature is : " << temp << endl;
		string type = GetType();
		string location = GetRoom();
		Event* temperatureEvent = new Event(ctime(&timer),"Temp_sensor_event", buff.str(), location , "maintenance");
		SendEventToHub(temperatureEvent);
		ZLOG_SEND(zlog, LOG_TRACE, "Temp sensor send event: %s" , temperatureEvent->GetType().c_str());
		Wait(12);
	}
}


