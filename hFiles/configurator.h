#ifndef __CONFIGURATOR_H__
#define __CONFIGURATOR_H__
#include <vector>
#include <string>
using namespace std;
class LogConfig;
class Reader;
class Parser;
class ConfigData;
class Configurator
{
public:
	Configurator( const string& _agentsFileName);
	~Configurator();
	vector<ConfigData>& GetAgentsConf();

protected:
	
private:
	Configurator(const Configurator& _conf) ;
	Configurator& operator=(const Configurator& _conf) ;
	

	const string m_agentsFile;
	Reader* m_reader;
	Parser* m_parser;
	vector<ConfigData> m_configs;
	ConfigData* m_confData;
			
};
#endif
