#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
#include <vector>
#include <utility> 
#include <iostream> 
using namespace std;
class ConfigData;

class Parser
{

public:
	Parser();
	~Parser();
	void ProcessLine(const string& _line);
	vector <ConfigData>& GetProcessedConfigs() ;
	
protected:
	
private:
	Parser(const Parser& _parser);
	Parser& operator=(const Parser& _parse);
	void CheckAndInsertToken(const string& _line);
	
	ConfigData* m_data;
	vector<ConfigData> m_allConfigs;
	
			
};
#endif
