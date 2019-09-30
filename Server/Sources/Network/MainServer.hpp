//
// Created by theo.zapata on 9/16/19.
//

#ifndef CPP_BABEL_2019_MAINSERVER_HPP
#define CPP_BABEL_2019_MAINSERVER_HPP

#include <list>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <memory>
#include <functional>
#include <poll.h>
#include <bits/unique_ptr.h>
#include "NetworkClient.hpp"
#include "Controller.hpp"

namespace Babel
{
namespace Network
{
template <typename T>
class MainServer
{
private:
    std::vector<std::shared_ptr<T>> clientList;

public:
    explicit MainServer(int port)
    {
        _port = port;
        _sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (_sd == -1)
            throw std::runtime_error("Socket creation failed");

        _sockaddrInServer.sin_family = AF_INET;
        _sockaddrInServer.sin_port = htons(port);
        _sockaddrInServer.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(_sd, (struct sockaddr *)(&_sockaddrInServer), sizeof(_sockaddrInServer)) == -1)
            throw std::runtime_error("Bind error");

        if (listen(_sd, 10) == -1)
            throw std::runtime_error("Listen error");
    }

    void run()
    {
        struct pollfd *pollfd = buildpollfdset();
        int retPoll = 0;

        while (_running)
        {
            retPoll = 0;
            for (int i = 0; i < clientList.size() + 1; i++)
            {
                std::cout << "Client nb : " << i << "has socket fd : " << pollfd[i].fd << std::endl;
            }
            retPoll = poll(pollfd, clientList.size() + 1, 1000);
            if (retPoll < 0)
            {
                throw std::runtime_error("pool error");
            }
            if (retPoll == 0)
            {
                std::cout << "Timeout" << std::endl;
                continue;
            }
            if (pollfd[0].revents == POLLIN)
            {
                struct sockaddr_in client = {};
                socklen_t socklen = sizeof(struct sockaddr_in);
                int newClientFd = accept(_sd, (sockaddr *)(&client), &socklen);
                clientList.push_back(std::unique_ptr<T>(new T(newClientFd, static_cast<struct sockaddr_in *>(&client))));
            }
            for (int i = 0; i < clientList.size(); i++)
            {
                if (pollfd[i + 1].revents & POLLIN)
                {
                    std::cout << "New message" << std::endl;
                    int r = receive(clientList.at(i));
                    if (r == 0)
                        clientList.erase(clientList.begin() + i);
                }
            }
            pollfd = buildpollfdset();
        }
    }
    //using ClientBaseT = T; // typename std::enable_if<std::is_base_of<Babel::Network::NetworkClient, T>::value>::type;

private:
    int _port = 0;
    struct sockaddr_in _sockaddrInServer = {0};
    int _sd = -1;

    bool _running = true;
    Controller<T> controller;
    struct pollfd *buildpollfdset()
    {
        size_t size = clientList.size();

        auto *fdSet = static_cast<pollfd *>(malloc(sizeof(struct pollfd) * (size + 1)));

        fdSet[0].fd = _sd;
        fdSet[0].events = POLLIN;
        for (size_t i = 1; i < size + 1; i++)
        {
            fdSet[i].fd = clientList[i - 1]->fd;
            fdSet[i].events = POLLIN;
        }
        return fdSet;
    }

    int receive(std::shared_ptr<T> client)
    {
        char buffread[22000] = {};
        int r = recv(client->fd, buffread, sizeof(buffread), 0);
        if (r == 0)
            return 0;
        printf("fd: %d | type: %d | recv %d: \n", client->fd, buffread[0], r);
        MessageType codeType = controller.manageReponse(client, static_cast<MessageType>(buffread[0]), buffread + 1);
        std::string reponse = controller.getReponse();
        std::cout << "reponse in server = " << reponse << std::endl;
        char *data = static_cast<char *>(malloc(sizeof(char) + sizeof(int) + reponse.length()));
    	data[0] = static_cast<char>(codeType);
	    int length = reponse.length();
	    int *tmp = (int *)&data[1]; //theo.zapata@epitech.eu tricks
	    (*tmp) = length;
    	memcpy(data + 5, reponse.c_str(), reponse.length());
        send(client->fd, data, sizeof(char) + sizeof(int) + reponse.length(), 0);
        return (1);
    }
};
} // namespace Network
} // namespace Babel

#endif //CPP_BABEL_2019_MAINSERVER_HPP
