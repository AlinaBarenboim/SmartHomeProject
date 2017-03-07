#ifndef __LIVE_LOG_H__
#define __LIVE_LOG__H__
#include <map>
#include <thread>
#include <string>
#include <vector>
template <typename T>
class SafeQueue;
class Tcp;
class Event;
class Agent;
class ConfigData;
class EventsHub;
using namespace std;
#include "../hFiles/agent.h"


class LiveLog : public Agent
{
public:
	LiveLog(const ConfigData& _conf,  const EventsHub* _hub);
	virtual ~LiveLog();	
	void ReceiveNewConnection(const string& _level, const string& _userName);
	void Join();
	
protected:
	
private:

	void RunAgent();
	void* ProcessEvent();
	void MakeListOfLogLevels(const ConfigData& _conf);
	void* WakeUpServer();
	LiveLog(const LiveLog& _log);
	LiveLog& operator=(const LiveLog& _log);
	
	map <string,vector <string>> m_usersAndLevels;
	Tcp* m_server; 
	SafeQueue<Event*>* m_connectsQueue;
	thread m_receiveThread;
	thread m_serverThread;
	string m_port;
	vector<string> m_logLevels;
	bool m_isAllLevels;
};
#endif

