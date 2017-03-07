#ifndef __LIVE_LOG_CREATOR_H__
#define __LIVE_LOG_CREATOR__H__
#include "../hFiles/agentCreator.h"
#include "../hFiles/liveLog.h"

class EventsHub;
class ConfigData;



class LiveLogCreator : public AgentCreator
{
public:
	LiveLogCreator(){}
	virtual ~LiveLogCreator(){}	
	Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub){return new LiveLog (_conf, _hub);}
		
protected:
	
private:
	LiveLogCreator(LiveLogCreator& _liveLogCreator);
	LiveLogCreator& operator=(const LiveLogCreator& _liveLogCreator);			
};


extern "C"
void* GetCreator();
#endif


