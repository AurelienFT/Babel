//
// Created by theo.zapata on 9/16/19.
//

#include <iostream>
#include <cstring>
#include "NetworkClient.hpp"

void Babel::Network::NetworkClient::onMessage(std::vector<uint8_t> &buff)
{
    printf("Message: %d {", fd);
    for (auto i : buff) {
        printf("%x", i);
    }
    printf("}\n");
}

Babel::Network::NetworkClient::NetworkClient(int fd, struct sockaddr_in *sockaddrIn) :
    fd(fd)
{
    memcpy(&sockaddrInClient, sockaddrIn, sizeof(struct sockaddr_in));
    std::cout << "New network client, id: " << fd << std::endl;
}

Babel::Network::NetworkClient::~NetworkClient()
{
    std::cout << "Network client " << fd  << "disconnected" << std::endl;
}
