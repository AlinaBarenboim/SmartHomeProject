#ifndef __SPRINKLER_CONTROLLER_H__
#define __SPRINKLER_CONTROLLER_H__
#include "../hFiles/agent.h"
class ConfigData;
class EventsHub;


class SprinklerController : public Agent
{
public:
	SprinklerController(const ConfigData& _conf,  const EventsHub* _hub);
	virtual ~SprinklerController();
	void Join();
		
protected:
	
private:
	SprinklerController(const SprinklerController& _sprinkCont);
	SprinklerController& operator=(const SprinklerController& _sprinkCont);
	void RunAgent();
	void* ProcessEvent();
	
	thread m_sendThread;		
};

#endif





