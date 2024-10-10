#include "Socket.h"

Socket::Socket() {
	WSADATA wsaData;

	sock = INVALID_SOCKET;
	memset(&addr, 0, sizeof(addr));
	errorCode = 0;

	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err) {
		std::cerr << "WSAStartup Error : " << WSAGetLastError() << std::endl;
		errorCode = WSAGetLastError();
		WSACleanup();
		return;
	}
}

Socket::~Socket() {
	WSACleanup();
}

BOOL Socket::create() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Create Socket Error : " << WSAGetLastError() << std::endl;
		errorCode = WSAGetLastError();
		WSACleanup();
		return FALSE;
	}

	std::cout << "create Socket" << std::endl;
	return TRUE;
}

BOOL Socket::bind(std::string& serverIp, std::string& serverPort) {
	inet_pton(AF_INET, serverIp.c_str(), &addr.sin_addr.s_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(serverPort.c_str()));

	if (::bind(sock, (sockaddr*)&addr, sizeof(addr))) {
		printf("Bind error : %d\n", WSAGetLastError());
		WSACleanup();
		return FALSE;
	}

	std::cout << "bind Socket" << std::endl;
	return TRUE;
}

BOOL Socket::listen(int backlog) {
	if (::listen(sock, backlog)) {
		printf("Listen error : %d\n", WSAGetLastError());
		WSACleanup();
		return FALSE;
	}

	std::cout << "listen Socket" << std::endl;
	return TRUE;
}

SOCKET Socket::accept() {
	int clnt_addr_size;
	SOCKET clnt_sock;
	sockaddr_in clnt_addr;

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = ::accept(sock, (sockaddr*)&clnt_addr, &clnt_addr_size);

	if (clnt_sock == INVALID_SOCKET) {
		printf("Accept error : %d\n", WSAGetLastError());
		WSACleanup();
		return INVALID_SOCKET;
	}

	std::cout << "accept Socket" << std::endl;
	return clnt_sock;
}

BOOL Socket::connect(std::string& ip, std::string& port) {
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port.c_str()));
	inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);

	int err = ::connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (err == SOCKET_ERROR) {
		printf("Connect Error : %d\n", WSAGetLastError());
		WSACleanup();
		return FALSE;
	}

	std::cout << "connect Socket" << std::endl;
	return TRUE;
}

void Socket::close() const {
	closesocket(sock);
	std::cout << "close Socket" << std::endl;
}
