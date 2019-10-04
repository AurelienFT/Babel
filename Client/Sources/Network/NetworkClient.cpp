/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** NetworkClient
*/

#include "NetworkClient.hpp"
#include <cstring>
#include <iostream>
#include <exception>

void NetworkClient::connection()
{
	SOCKADDR_IN servAddress;
#ifdef linux
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	servAddress.sin_family = AF_INET;
	servAddress.sin_port = htons(PORT);

	if (inet_pton(AF_INET, SERVER_ADDRESS, &servAddress.sin_addr) <= 0)
		throw std::exception();
#endif
#ifdef _WIN64
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	servAddress.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
	servAddress.sin_family = AF_INET;
	servAddress.sin_port = htons(PORT);
#endif
	if (connect(_sockfd, (struct sockaddr *)&servAddress, sizeof(servAddress)) < 0)
		throw std::exception();
#ifdef _WIN64
	unsigned long l = 1;
	ioctlsocket(_sockfd, FIONBIO, &l);
#endif
}

MessageType NetworkClient::receive_messageCode()
{
	char buffread[22000] = {0};
	char messageType = 0;
	recv(_sockfd, (char*)&buffread, sizeof(buffread), 0);
	int size = *(int *)(buffread + 1);
	std::cout << "size in network: " << size << std::endl;
	static const int array_size = size + 1;
	char tmp[10000] = {0};// TO CHANGE for windows test
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
	return 0;
}

void NetworkClient::disconnect()
{
	closesocket(_sockfd);
}