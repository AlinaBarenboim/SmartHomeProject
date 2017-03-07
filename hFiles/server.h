#ifndef __TCP_H__
#define __TCP_H__
#include <string>
#include "../hFiles/event.h"

using namespace std;
class Tcp
{
public:
	Tcp():m_isConnected(false){}
	~Tcp(){};	
	void RunTcpServer(const string& _port);
	void Send (Event* _event);
	
protected:
	
private:

	Tcp(const Tcp& _tcp);
	Tcp& operator=(const Tcp& _tcp);
	void* get_in_addr(struct sockaddr * sa);

	bool m_isConnected;
	int m_fd;
};
#endif
