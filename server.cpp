#include <iostream>
#include "Socket.h"

int main() {
	Socket server;
	std::string ip = "127.0.0.1";
	std::string port = "9190";

	server.create();
	server.bind(ip, port);
	server.listen(5);
	server.accept();
	server.close();

	return 0;
}