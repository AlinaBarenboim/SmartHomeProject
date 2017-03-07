#include "../hFiles/parser.h"
#include "../hFiles/configData.h"
#include <string>
#include <utility>      
#include <iostream>     
using namespace std;

Parser::Parser()
{
	m_data = new ConfigData;
}

Parser::~Parser()
{
	delete m_data;
}


void  Parser::ProcessLine(const string& _line)
{

	if(!_line.empty())
	{
		CheckAndInsertToken(_line);
	}
	else //if it is an end of configuration section
	{
		m_allConfigs.push_back(*m_data);
		delete m_data;
		m_data = new ConfigData;
	}
}

vector <ConfigData>& Parser::GetProcessedConfigs() 
{
	return m_allConfigs;
}


void Parser::CheckAndInsertToken(const string& _line)
{
	int position = 0;
	int endPos;
	int finalPos;
	if (position == _line.find_first_of("["))
	{
		endPos = _line.find_first_of("]");
		m_data->SetData ("id", _line.substr(position+1,endPos-1));	
	}
	else
	{
		endPos = _line.find_first_of("=");
		string key = _line.substr(position,endPos-1);
		finalPos = _line.find_first_of("\n");
		string value = _line.substr(endPos+2,finalPos-1);
		m_data->SetData (key,value);		
	}
}
