#ifndef __APP_H__
#define __APP__H__
class Configurator;
class AgentLifeCycleMng;
class ConfigData;
class AgentFactory;

class Application

{
public:
	Application(){};
	~Application();	
	void RunApplication (const string& _fileName);
		
protected:
	
private:
	Application(const Application& _app);
	Application& operator=(const Application& _app);
	void LoadCreators(ConfigData& _data, AgentFactory& _factory);
	
	Configurator* m_configurator;
	EventsHub* m_hub;
	AgentLifeCycleMng* m_agensLiveCyc;
	vector<string> m_creators;	
};
#endif
