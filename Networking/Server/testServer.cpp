#include "./testServer.hpp"
#include <cstring>
#include <istream>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <unistd.h>

Socketing::testServer::testServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 1024, INADDR_ANY, 10)
{
	std::cout << " INAADRRRR " << INADDR_ANY << std::endl;
	this->socket = NULL;
	new_socket = 0;
	launch();
}


void	Socketing::testServer::accepter()
{
	// std::cout << "Ici ???? " << std::endl;
	sockaddr_in add = get_server_socket()->get_address();
	int addrlen = sizeof(add);
	new_socket = accept(get_server_socket()->get_sock(), (struct sockaddr *)&add, (socklen_t *)&addrlen);
	read(new_socket, this->buffer, 30000);
}


void	Socketing::testServer::handler()
{
	std::cout << buffer << std::endl;
}

void	Socketing::testServer::responder()
{
	std::cout << "wesh 0" << std::endl;
	const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	write(new_socket, hello, strlen(hello));
	std::cout << new_socket << std::endl;
	close(new_socket);
}

void	Socketing::testServer::launch()
{
	while(true)
	{
		std::cout << "==========Waiting===========" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "==========Done===========" << std::endl;
	}
}
