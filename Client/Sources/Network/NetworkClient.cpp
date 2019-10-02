/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** NetworkClient
*/

#include "NetworkClient.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

void NetworkClient::connection()
{
	int connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(_sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
}

MessageType NetworkClient::receive_messageCode()
{
	char buffread[22000] = {0};
	char messageType = 0;
	recv(_sockfd, &buffread, sizeof(buffread), 0);
	int size = *(int *)(buffread + 1);
	std::cout << "size in network: " << size << std::endl;
	char tmp[size + 1] = {0};
	memcpy(tmp, buffread + 5, size);
	_reponse = std::string(tmp);
	std::cout << "reponse in network: " << _reponse << std::endl;
	return static_cast<MessageType>(buffread[0]);
}

std::string NetworkClient::getReponse() const
{
	return (_reponse);
}


int NetworkClient::send_server(MessageType messageType, std::string message)
{
	char *data = static_cast<char *>(malloc(sizeof(char) + sizeof(int) + message.length()));
	data[0] = static_cast<char>(messageType);
	int length = message.length();
	int *tmp = (int *)&data[1]; //theo.zapata@epitech.eu tricks
	(*tmp) = length;
	memcpy(data + 5, message.c_str(), message.length());
	send(_sockfd, data, sizeof(char) + sizeof(int) + message.length(), 0);
}

void NetworkClient::disconnect()
{
	close(_sockfd);
}