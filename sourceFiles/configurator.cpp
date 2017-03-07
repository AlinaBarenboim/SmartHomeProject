#include <vector>
#include "../hFiles/configurator.h"
#include <string>
#include "../hFiles/reader.h"
#include "../hFiles/parser.h"
#include "../hFiles/configData.h"
#include <iostream>
using namespace std;

Configurator::Configurator( const string& _agentsFileName) :  m_agentsFile(_agentsFileName)
{
	m_reader = new Reader();
	m_parser = new Parser();
	m_confData = new ConfigData();
}

Configurator::~Configurator()
{
	delete m_reader;
	delete m_parser;
	delete m_confData;
}

vector<ConfigData>& Configurator:: GetAgentsConf()
{
	m_configs.clear();
	m_reader->ProcessFile(m_agentsFile);
	while(m_reader->ismoreLines())
	{
		string newLine = m_reader->GetNextLine();		
		m_parser->ProcessLine(newLine);
	}	
	m_configs = m_parser->GetProcessedConfigs();	
	return m_configs;

}

