#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__
#include "../hFiles/agent.h"
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
using namespace std;
class ConfigData;
class EventsHub;

class Elevator : public  Agent
{
public:
	Elevator(const ConfigData& _conf,  const EventsHub* _hub);
	~ Elevator();
	void Join();
		
protected:

	virtual string GetLocation() const { stringstream buff;buff<< m_currFloor << endl; return buff.str();}
	
private:
	Elevator( const Elevator& _elevator);
	void operator=(const  Elevator& _elevator);
	void RunAgent() ;
	void* ProcessEvent();
	void* GenerateEvent();
	
	int m_currFloor;
	thread m_receiveThread;
	thread m_sendThread;
};

#endif




