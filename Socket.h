#pragma once
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class Socket {
private:
	SOCKET sock;
	sockaddr_in addr;
	int errorCode;
public:
	Socket();
	~Socket();
	BOOL create();
	BOOL bind(std::string& serverIp, std::string& serverPort);
	BOOL listen(int backlog);
	SOCKET accept();
	BOOL connect(std::string& ip, std::string& port);
	void close() const ;
};