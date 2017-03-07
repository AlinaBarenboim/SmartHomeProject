#include "../hFiles/liveLog.h"
#include "../hFiles/eventsHub.h"
#include "../hFiles/configData.h"
#include "../hFiles/agent.h"
#include "../hFiles/event.h"
#include "../hFiles/server.h"
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>

extern "C"
{
#include "../logger/inc/logmngr.h"
}

LiveLog::LiveLog(const ConfigData& _conf,  const EventsHub* _hub) :Agent(_conf,_hub ,true), m_port (_conf.GetValue("port")) , m_isAllLevels(false)
{
	Zlog* zlog;
	zlog = ZlogGet("mod2");
	UpdateAgentActionsAndLocation("log_levels");
	try 
	{
		MakeListOfLogLevels(_conf);
	}catch (const std::out_of_range& e)
	{
		ZLOG_SEND(zlog, LOG_TRACE, "out of range error catch, %s", _conf.GetValue("id").c_str() );
	}

	m_server = new Tcp();
	RunAgent();
}

void LiveLog::Join()
{
	m_receiveThread.join();
	m_serverThread.join();
}

LiveLog::~LiveLog() 
{
	delete m_server;
}

void LiveLog:: RunAgent ()
{
	m_receiveThread = thread([this] {ProcessEvent();});
	m_serverThread = thread([this] {WakeUpServer();});
}


void* LiveLog:: WakeUpServer()
{
	m_server->RunTcpServer(m_port);
}

void* LiveLog:: ProcessEvent()
{
	Zlog* zlog;
	zlog = ZlogGet("mod1");
	while (1)
	{
		Event* newEvent = (Event*)GetNewEvent();
		ZLOG_SEND(zlog, LOG_TRACE, "New event received in live log agent: %s" , newEvent->GetType().c_str());
//		string timer = newEvent->GetTime();		
//		string location = newEvent->GetLocation();
//		string type = newEvent->GetType();
//		string data = newEvent->GetData();
//		string log = newEvent->GetLog();
//		cout<< "******LIVE LOG EVENT ******"<<endl;
//		cout << "EVENT DATA : "<< data <<endl;
//		cout <<  "EVENT TYPE :"<< type << endl;
//		cout << "EVENT TIME : " << timer <<endl;
//		cout << "EVENT LOCATION :" << location <<endl;
//		cout << "EVENT LOG LEVEL :" << log << endl;
//		cout <<  "*********************" << endl;	
		string log = newEvent->GetLog();
		vector<string>:: iterator it =  find (m_logLevels.begin(), m_logLevels.end(), log);

		if (m_isAllLevels != true)
		{
			if (it != m_logLevels.end())
			{
				ZLOG_SEND(zlog, LOG_TRACE, "LOG SEND THIS EVENT TO SERVER...: %s" , newEvent->GetType().c_str());
				m_server->Send(newEvent);
			}
			else
			{
				ZLOG_SEND(zlog, LOG_TRACE, "LOG NOT SEND THIS EVENT TO SERVER...: %s" , newEvent->GetType().c_str());
			}
		}
		else
		{
			m_server->Send(newEvent);
			ZLOG_SEND(zlog, LOG_TRACE, "LOG SEND THIS EVENT TO SERVER...: %s" , newEvent->GetType().c_str());
		}
		
	delete newEvent;
	}
}

void LiveLog::MakeListOfLogLevels(const ConfigData& _conf)
{
	Zlog* zlog;
	zlog = ZlogGet("mod2");	
	string logs = _conf.GetValue("log");
	if (logs == "all")
	{
		m_logLevels.push_back(logs);
		m_isAllLevels = true;
 		return;
	}
	size_t pos , tempPos = 0 ;
	size_t size = logs.size();
	while (tempPos <= size)
	{
		string level;
		size_t endPos = logs.find("|");
 		if (endPos /*)==std ::string::npos*/ > size)
 		{
 			m_logLevels.push_back(logs);
 			ZLOG_SEND(zlog, LOG_TRACE, "log level for server %s" ,logs.c_str());
 			throw std::out_of_range ("out_of_range");
 		}
 		else
 		{
	 		level = logs.substr(pos,endPos);
			m_logLevels.push_back(level);
			vector<string>:: iterator it = m_logLevels.begin();//for debug only
			for (it; it != m_logLevels.end(); ++it)
			{
				ZLOG_SEND(zlog, LOG_TRACE, "log level for server %s" ,(*it).c_str());
			}			
		
			logs = logs.substr(endPos+1,logs.size());	
			tempPos = endPos + 1;	
			pos= 0;
			endPos = 0;
 		}
	}
	return;
}




