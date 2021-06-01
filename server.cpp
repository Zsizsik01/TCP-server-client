#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

int main()
{
	std::cout << "Waiting for connection..." << std::endl;

	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == 0)
	{
		std::cout << "Failed to create a socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(9999);

	if(bind(socketfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		std::cout << "Binding has failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	if(listen(socketfd, 10) < 0)
	{
		std::cout << "Listening has failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	auto addrlen = sizeof(sockaddr);
	int connection = accept(socketfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if(connection < 0)
	{
		std::cout << "Connection has failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Connection was success..." << std::endl;

	char buffer[100] = {0};
	auto bytesRead = read(connection, buffer, 100);
	std::cout << "The message from client: " << buffer << std::endl;

	std::string answer = "Hello from server";
	send(connection, answer.c_str(), answer.size(), 0);

	close(connection);
	close(socketfd);

	return 0;
}