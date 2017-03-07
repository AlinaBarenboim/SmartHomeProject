#ifndef __EVENT_H__
#define __EVENT_H__
#include <string>
using namespace std;

class Event
{
public:
	Event(){};
	Event(const string _time,const string _type, const string _data, const string _location, const string _log );
	~Event(){};
	const string& GetTime() const{ return m_time;}
	const string& GetType() const{ return m_type;}
	const string& GetData() const{ return m_data;}
	const string& GetLocation() const{return m_location;}
	const string& GetLog() const{return m_log;}
		
protected:
	
private:
	//Event(const Event& _event);
	//Event& operator=(const Event& _event);
	
	string m_time;
	string m_type;
	string m_data;
	string m_location;
	string m_log;

			
};
#endif
