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
#include <poll.h>
#include <bits/unique_ptr.h>
#include "NetworkClient.hpp"


namespace Babel {
    namespace Network {

        template<typename T>
        class MainServer {
        private:
            std::vector<std::unique_ptr<T >> clientList;

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

                if (bind(_sd, (struct sockaddr *) (&_sockaddrInServer), sizeof(_sockaddrInServer)) == -1)
                    throw std::runtime_error("Bind error");

                if (listen(_sd, 10) == -1)
                    throw std::runtime_error("Listen error");
            }

            void run()
            {
                _pollfdsSize = 1;
                struct pollfd *pollfd = buildpollfdset();
                int retPoll = 0;

                while (_running) {
                    retPoll = 0;
                    for (int i = 0; i < clientList.size() + 1; i++) {
                        std::cout << "Client nb : " << i << "has socket fd : " << pollfd[i].fd << std::endl;
                    }
                    retPoll = poll(pollfd, clientList.size() + 1, 1000);
                    if (retPoll < 0) {
                        throw std::runtime_error("pool error");
                    }
                    if (retPoll == 0) {
                        std::cout << "Timoute" << std::endl;
                        continue;
                    }
                    if (pollfd[0].revents == POLLIN) {
                        std::cout << "accept" << std::endl;
                        struct sockaddr_in client = {};
                        socklen_t socklen = sizeof(struct sockaddr_in);
                        int newClientFd = accept(_sd, (sockaddr *) (&client), &socklen);
                        clientList.push_back(std::unique_ptr<T>(new T(newClientFd, static_cast<struct sockaddr_in *>(&client))));
                    }
                    for (int i = 0; i < clientList.size(); i++) {
                        if (pollfd[i + 1].revents & POLLIN) {
                            std::cout << "New message" << std::endl;
                            char buffread[22000] = {};
                            std::cout << "in loop 2.1 " << pollfd[i + 1].fd << std::endl;
                            int r = recv(pollfd[i + 1].fd, buffread, sizeof(buffread), 0);
                            printf("recv %d: \n", r);
                            for (int y = 0; y < r; y++)
                                printf("%c ", buffread[y]);
                            printf("\n");
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

            struct pollfd *_pollfds = nullptr;
            uint32_t _pollfdsSize = 0;


            struct pollfd *buildpollfdset()
            {
                size_t size = clientList.size();

                auto *fdSet = static_cast<pollfd *>(malloc(sizeof(struct pollfd) * (size + 1)));

                fdSet[0].fd = _sd;
                fdSet[0].events = POLLIN;
                for (size_t i = 1; i < size + 1; i++) {
                    fdSet[i].fd = clientList[i - 1]->_fd;
                    fdSet[i].events = POLLIN;
                }
                return fdSet;
            }
        };
    }
}

#endif //CPP_BABEL_2019_MAINSERVER_HPP
