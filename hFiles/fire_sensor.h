#ifndef __FIRE_SENSOR_H__
#define __FIRE_SENSOR_H__
class ConfigData;
class EventsHub;
#include "../hFiles/agent.h"

class FireDetector : public Agent
{
public:
	FireDetector(const ConfigData& _conf,  const EventsHub* _hub);
	virtual ~FireDetector();
	static void GenerateEvent();
	void Join();
		
protected:
	
private:

	FireDetector(const FireDetector& _fireSens);
	FireDetector& operator=(const FireDetector& _fireSens);
	void* WaitForEvent();
	void RunAgent() ;
	
	thread m_sendThread;
	static FireDetector* m_fireDetector;		
};

void SignalHandlerFunc(int signum);
#endif
