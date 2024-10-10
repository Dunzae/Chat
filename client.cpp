#include <iostream>
#include "Socket.h"

int main() {
	Socket client;
	std::string ip = "127.0.0.1";
	std::string port = "9190";

	client.create();
	client.connect(ip, port);
	client.close();

	return 0;
}