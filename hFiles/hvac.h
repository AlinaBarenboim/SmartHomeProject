#ifndef __HVAC_H__
#define __HVAC_H__
class ConfigData;
class EventHub;
#include <thread>
#include <string>
#include "../hFiles/agent.h"

class HVAC : public Agent
{
public:
	HVAC(const ConfigData& _conf,  const EventsHub* _hub);
	virtual ~HVAC();
	void Join();
		
protected:
	
private:
	HVAC(const HVAC& _hvac);
	HVAC& operator=(const HVAC& _hvac);
	void RunAgent() ;
	void* ProcessEvent();
	
	thread m_receiveThread;

	 

};
#endif


