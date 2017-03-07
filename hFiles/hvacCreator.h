#ifndef __HVAC_CREATOR_H__
#define __HVAC_CREATOR__H__
#include "../hFiles/hvac.h"
#include "../hFiles/agentCreator.h"
class AgentCreator;
class HVAC;
class EventHub;
class ConfigData;

class HVACCreator : public AgentCreator
{
public:
	HVACCreator(){};
	virtual ~HVACCreator(){};	
	Agent* CreateAgent (const ConfigData& _conf,  const EventsHub* _hub){return new HVAC (_conf, _hub );}
		
protected:
	
private:
	HVACCreator(const HVACCreator& _hvacCreator);
	HVACCreator& operator=(const HVACCreator& _hvacCreator);			
};


extern "C"
void* GetCreator();
#endif
