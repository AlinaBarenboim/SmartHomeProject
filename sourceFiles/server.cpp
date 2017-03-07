#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string>
#include <iostream>
#include <unistd.h>
#include <sstream>  
#include <iomanip>
#include "../hFiles/server.h"
#include "../hFiles/event.h"
#include <ctime>
using namespace std;
//Colours codes 
//#define RESET   "\033[0m"
//#define BLACK   "\033[30m"      /* Black */
//#define RED     "\033[31m"      /* Red */
//#define GREEN   "\033[32m"      /* Green */
//#define YELLOW  "\033[33m"      /* Yellow */
//#define BLUE    "\033[34m"      /* Blue */
//#define MAGENTA "\033[35m"      /* Magenta */
//#define CYAN    "\033[36m"      /* Cyan */
//#define WHITE   "\033[37m"      /* White */
//#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
//#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
//#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
//#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
//#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
//#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
//#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
//#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


void* Tcp:: get_in_addr(struct sockaddr* sa)
{
	if(sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr); 
	}
	
	return &(((struct sockaddr_in6 *)sa)->sin6_addr); 
}

void Tcp::RunTcpServer(const string& _port)
{
	cout << "\033[1m\033[35m PORT NUMBER : \033[0m"<< _port << endl;
	int status;
	struct addrinfo hints, * res;
	int listner; 	
	//empty data structure
	memset(& hints, 0, sizeof hints);
	// Set the attribute for hint
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 	
	status = getaddrinfo(NULL, _port.c_str() , &hints, &res);
	if(status != 0)
	{
		fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(status));
	}
	listner = socket(res->ai_family,res->ai_socktype, res->ai_protocol);
	if(listner < 0 )
	{
		fprintf(stderr,"socket error: %s\n",gai_strerror(status));
	}
	
	// Bind the socket to the  port number 
	status = bind(listner, res->ai_addr, res->ai_addrlen); 
	if(status < 0)
	{
		fprintf(stderr,"bind: %s\n",gai_strerror(status));
	}
	status = listen(listner, 10); 
	if(status < 0)
	{
		fprintf(stderr,"listen: %s\n",gai_strerror(status));
	}
	freeaddrinfo(res);
	
	// wait now for a connection to accept
	int new_conn_fd;
	struct sockaddr_storage client_addr;
	socklen_t addr_size;
	char s[INET6_ADDRSTRLEN];		
	// Calculate the size of the data structure	
	addr_size = sizeof client_addr;	
	//printf("I am now accepting connections ...\n");
	cout << "\033[1m\033[35m Server is connected now.... \033[0m" << endl;
	
	while(1){
		// Accept a new connection and return back the socket desciptor 
		new_conn_fd = accept(listner, (struct sockaddr *) & client_addr, &addr_size);	
		if(new_conn_fd < 0)
		{
			fprintf(stderr,"accept: %s\n",gai_strerror(new_conn_fd));
			continue;
		}
	
		inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *) &client_addr),s ,sizeof s); 
		cout << "\033[1m\033[35m Server now connected to  \033[0m" << s << endl;
		m_isConnected = true;
		m_fd = new_conn_fd;
		
	}

	close(new_conn_fd);	
	m_isConnected = false;
	return ;
}



void Tcp:: Send (Event* _event)
{
	if (m_isConnected)
	{
		string event  =  _event->GetData();
		string time = _event->GetTime();			
		string location = _event->GetLocation();
		string data = _event->GetType();
		string log = _event->GetLog();
		string buff;
		if (log == "maintenance")
		{
			buff = "\033[1m\033[32m" + time + data +  event + "Location :"  + location +  "\n";
		}
		else if (log == "safety")
		{
			buff = "\033[1m\033[31m" + time + data + event + "Location :" + location + "\n";
		}
		else if (log == "Elevator_action")
		{
			buff = "\033[1m\033[34m"  + time + data + event  + "Location :" + location  + "\n";
		}
		else 
		{
			buff = "\033[1m\033[35m"  + time + data + event  + "Location :" + location  + "\n";
		}

		int status = send(m_fd,buff.c_str(),buff.length(),0);
		if(status == -1)
		{
			close(m_fd);
			throw ("send error");
		}
		buff.clear();	
	}		
}
