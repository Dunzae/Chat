#include <iostream>
#include <thread>
#include "Socket.h"

static void serverStart() {
	Socket server;
	std::string ip = "127.0.0.1";
	std::string port = "9190";

	server.create();
	server.bind(ip, port);
	server.listen(5);
	server.accept();
	server.close();
}

static void clientStart() {
	Socket client;
	std::string ip = "127.0.0.1";
	std::string port = "9190";

	client.create();
	client.connect(ip, port);
	client.close();
}

int main(int argc, char** argv) {
	std::thread t1(serverStart );
	std::thread t2(clientStart);

	t1.join();
	t2.join();

	return 0;
}