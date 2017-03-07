#ifndef __FIRE_SENSOR_CREATOR_H__
#define __FIRE_SENSOR_CREATOR__H__
#include "../hFiles/agentCreator.h"
#include "../hFiles/fire_sensor.h"
class AgentCreator;
class EventsHub;

class FireSensorCreator : public AgentCreator
{
public:
	FireSensorCreator(){}
	virtual ~FireSensorCreator(){}
	Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub) {return new FireDetector(_conf , _hub);}
		
protected:
	
private:
	FireSensorCreator(const FireSensorCreator& _fireSensCreator);
	FireSensorCreator& operator=(const FireSensorCreator& _fireSensCreator);			
};


extern "C"
void* GetCreator();

#endif


