#ifndef __CONFIG_DATA_H__
#define __CONFIG_DATA_H__
#include <vector>
#include <string>
#include <map>
using namespace std;

class ConfigData
{

public:
	ConfigData() : m_currField(0) {}
	~ConfigData(){};
	void SetData (const string& _key, const string& _value){ m_configs[_key] = _value;}
	const string& GetValue(const string& _key) const;
	const map<string,string>& GetAllConfig() const {return m_configs;}
	
protected:
	
private:

	int m_currField;
	map<string,string> m_configs;

};
#endif
