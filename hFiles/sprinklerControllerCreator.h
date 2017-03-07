#ifndef __SPRINKLER_CONTROLLER_CREATOR_H__
#define __SPRINKLER_CONTROLLER_CREATOR__H__
#include "../hFiles/agentCreator.h"
#include "../hFiles/sprinkler_controller.h"

class EventsHub;

class SprinklerControllerCreator : public AgentCreator
{
public:
	SprinklerControllerCreator(){}
	virtual ~SprinklerControllerCreator(){}	
	Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub){return new SprinklerController(_conf , _hub) ;}
		
protected:
	
private:
	SprinklerControllerCreator(const SprinklerControllerCreator& _sprinkContCreator);
	SprinklerControllerCreator& operator=(const SprinklerControllerCreator& _sprinkContCreator);			
};

extern "C"
void* GetCreator();
#endif



