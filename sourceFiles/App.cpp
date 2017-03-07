#include "../hFiles/configData.h"
#include "../hFiles/agentlifeCicleMng.h"
#include "../hFiles/eventsHub.h"
#include "../hFiles/agentFactory.h"
#include "../hFiles/App.h"
#include "../hFiles/configurator.h"
extern "C"
{
#include "../logger/inc/logmngr.h"
}
#include <string>
#include <vector>
#include <dlfcn.h>
#include<algorithm>

typedef void* (*FUNC)();

void  Application::LoadCreators( ConfigData& _data, AgentFactory& _factory)
{

	Zlog* zlog;
	zlog = ZlogGet("mod1");
	
	string creator = _data.GetValue("type");
	string path = "./" + creator + ".so";

	vector<string>:: iterator itr = find(m_creators.begin(), m_creators.end(),_data.GetValue("type"));
	if (itr == m_creators.end())
	{
		void* handle =  dlopen( path.c_str() , RTLD_LAZY);
		FUNC func = (FUNC)dlsym(handle,"GetCreator");
		AgentCreator* _creator =(AgentCreator* )func();
		_factory.AddCreator(_data.GetValue("type"), _creator);
		m_creators.push_back(_data.GetValue("type"));
		ZLOG_SEND(zlog, LOG_TRACE, "new creator added successfully : %s" , creator.c_str());
	}
}

void Application::RunApplication (const string& _fileName)
{
	m_configurator = new Configurator (_fileName);
	vector<ConfigData> agensConfigs = m_configurator->GetAgentsConf();
	AgentFactory& factory = AgentFactory::GetInstance();	
	vector<ConfigData>:: iterator it = agensConfigs.begin();
	for (it ; it != agensConfigs.end(); ++it)
	{
		LoadCreators(*it, factory);
	}

	m_hub = new EventsHub();
	m_agensLiveCyc = new AgentLifeCycleMng(&factory, m_hub);
	m_agensLiveCyc->CreateAgent(agensConfigs);
	m_hub->EventHubRun();	
	m_hub->Join();
	m_agensLiveCyc->JoinAll();
}


Application::~Application()
{
	if (m_hub)
	{
		delete m_hub;
		m_hub = 0;

	}

	if (m_agensLiveCyc)
	{
		delete m_agensLiveCyc;
		m_agensLiveCyc = 0;
	
	}
	
	if (m_configurator)
	{
		delete m_configurator;
		m_configurator = 0;
	
	}
	
}	

int main () //test
{

	Application* app = new Application();
	Zlog* zlog;
	ZlogInit("log_config");
	zlog = ZlogGet("mod1");
	app->RunApplication ("config.txt");
}
