//
// Created by theo.zapata on 10/1/19.
//

#ifdef __linux__
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#endif
#include <cstring>
#include <iostream>
#include "VoIp.hpp"

Babel::VoIpNetwork::VoIp::VoIp() : _runnig(false)
{
    struct sockaddr_in sockAddrInMe{};

    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock == -1)
        throw std::runtime_error(std::strerror(errno));

    sockAddrInMe.sin_family = AF_INET;
    sockAddrInMe.sin_port = 0; // User automatic port selection
    sockAddrInMe.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(_sock, reinterpret_cast<const sockaddr *>(&sockAddrInMe),
        sizeof(sockAddrInMe)) == -1)
        throw std::runtime_error(std::strerror(errno));
}

void Babel::VoIpNetwork::VoIp::threadLoop()
{
    ssize_t len = 0;
    uint8_t buff[2000];
    struct sockaddr_in sockAddrInNewClient{};
    socklen_t sockAddrInNewClientLen = sizeof(sockAddrInNewClient);

    while (_runnig) {
        std::cout << "WAITING CONNEXION" << std::endl;
        std::cout << "port = " << getPort() << std::endl;
        len = recvfrom(_sock, buff, sizeof(buff), MSG_WAITALL,
            reinterpret_cast<sockaddr *>(&sockAddrInNewClient), &sockAddrInNewClientLen);
        std::cout << "CONNEXION" << std::endl;
        if (len == -1) {
            std::cerr << "Doped packet" << std::endl;
            continue;
        }

        if (buff[0] == NEW_VOIP_CLIENT_CONNECTED && isNewClient(&sockAddrInNewClient, sockAddrInNewClientLen)) {
            addClient(&sockAddrInNewClient, sockAddrInNewClientLen);
            if (clientNumber == VOIP_MAX_CLIENT_NUMBER) {
                sendDialingDataToClient();
            }
        }
    }
}

void Babel::VoIpNetwork::VoIp::run()
{
    _runnig = true;
    netLoop = std::thread(&VoIp::threadLoop, this);
}

void Babel::VoIpNetwork::VoIp::stop()
{
    _runnig = false;
    netLoop.detach();
}

int Babel::VoIpNetwork::VoIp::getPort()
{
    struct sockaddr_in sockAddrInMe{};
    socklen_t sockAddrInMeLen = sizeof(sockAddrInMe);

    if (getsockname(_sock, reinterpret_cast<sockaddr *>(&sockAddrInMe), &sockAddrInMeLen) == -1)
        throw std::runtime_error(std::strerror(errno));
    return htons(sockAddrInMe.sin_port);
}

bool Babel::VoIpNetwork::VoIp::isNewClient(const struct sockaddr_in *newClient, socklen_t newClientLen)
{
    for (auto &i : sockAddrInClientList) {
        if (i.sin_family == newClient->sin_family &&
            i.sin_addr.s_addr == newClient->sin_addr.s_addr &&
            i.sin_port == newClient->sin_port)
            return false;
    }
    return true;
}

void Babel::VoIpNetwork::VoIp::addClient(const struct sockaddr_in *newClient, socklen_t newClientLen)
{
    sockAddrInClientLenList[clientNumber] = newClientLen;
    memcpy(&sockAddrInClientList[clientNumber++], newClient, newClientLen);
}

void Babel::VoIpNetwork::VoIp::sendDialingDataToClient()
{
    for (int i = 0; i < REDONDANCE_SENDING; i++) {
        sendto(_sock, &sockAddrInClientList[0], sockAddrInClientLenList[0], 0,
            reinterpret_cast<const sockaddr *>(&sockAddrInClientList[1]), sockAddrInClientLenList[1]);
        sendto(_sock, &sockAddrInClientList[1], sockAddrInClientLenList[1], 0,
            reinterpret_cast<const sockaddr *>(&sockAddrInClientList[0]), sockAddrInClientLenList[0]);
    }
}
