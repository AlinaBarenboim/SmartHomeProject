#ifndef __ELEVATOR_CREATOR_H__
#define __ELEVATOR_CREATOR__H__
#include "../hFiles/agentCreator.h"
#include "../hFiles/elevator.h"
class EventsHub;
class ConfigData;

class ElevatorCreator : public AgentCreator
{
public:
	ElevatorCreator(){};
	virtual ~ElevatorCreator(){};	
	virtual Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub){return new Elevator (_conf, _hub);}
	
protected:
	
private:
	ElevatorCreator(const ElevatorCreator& _elevCreator);
	ElevatorCreator& operator=(const ElevatorCreator& _elevCreator);
};


extern "C"
void* GetCreator();

#endif

