#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__
class ConfigData;
class EventsHub;
#include <thread>
#include <string>
#include "../hFiles/agent.h"

class TempSensor : public Agent
{
public:
	TempSensor(const ConfigData& _conf,  const EventsHub* _hub);
	virtual ~TempSensor();
	void Join();
	
protected:
	
private:
	TempSensor(const TempSensor& _tempSens);
	TempSensor& operator=(const TempSensor& _tempSens);
	void RunAgent();
	void GenerateEvent();
	void Wait( int seconds) const;
	
	thread m_sendThread;		
};
#endif

