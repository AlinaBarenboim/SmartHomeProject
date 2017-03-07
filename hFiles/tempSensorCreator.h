#ifndef __TEMP_SENSOR_CREATOR_H__
#define __TEMP_SENSOR_CREATOR__H__
#include "../hFiles/temp_sensor.h"
#include "../hFiles/agentCreator.h"
class EventsHub;
class ConfigData;

class TempSensorCreator : public AgentCreator
{
public:
	TempSensorCreator(){}
	virtual ~TempSensorCreator(){}	
	Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub){return new TempSensor (_conf, _hub);}
		
protected:
	
private:
	TempSensorCreator(TempSensorCreator& _tempSensCreator);
	TempSensorCreator& operator=(const TempSensorCreator& _tempSensCreator);			
};


extern "C"
void* GetCreator();
#endif


