#include "../hFiles/event.h"
#include <string>

Event::Event(const string _time,const string _type, const string _data, const string _location , const string _log ): m_time(_time), m_type(_type), m_data(_data), m_location(_location), m_log(_log){}

