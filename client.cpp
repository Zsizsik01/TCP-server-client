#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == 0)
	{
		std::cout << "Failed to create a socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(9999);

	if(inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr) <= 0)
	{
		std::cout << "Invalid address. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	if(connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		std::cout << "Connection has failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "What would you like to send to the server?" << std::endl;
	std::string message;
	getline(std::cin, message);

	send(sockfd, message.c_str(), message.size(), 0);
	std::cout << "Message sent" << std::endl;
	char buffer[100] = {0};
	auto byteRead = read(sockfd, buffer, 100);
	std::cout << "The message from server: " << buffer << std::endl;

        close(sockfd);

	return 0;
}
