#include "../hFiles/configData.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;



const string& ConfigData::GetValue(const string& _key)const
{
	map<string,string>:: const_iterator iter = m_configs.find(_key);
	if (iter != m_configs.end())
	{
		return (*iter).second;
	}
	else
	{
		throw "iterator points to end of map";
	}
}
