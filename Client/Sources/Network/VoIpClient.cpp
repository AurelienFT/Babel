//
// Created by theo.zapata on 10/4/19.
//

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>
#include "Server/Sources/Network/VoIp.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "VoIpClient.hpp"

Babel::VoIpNetwork::VoIpClient::VoIpClient(const std::string &ip, int port) : _port(port)
{
    sockaddr_in dst{};
    if (inet_pton(AF_INET, ip.c_str(), &dst.sin_addr) <= 0)
        throw std::runtime_error(std::strerror(errno));
    dst.sin_port = htons(_port);

    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock == -1)
        throw std::runtime_error(std::strerror(errno));

    uint8_t data = VOIP_CODE::NEW_VOIP_CLIENT_CONNECTED;
    sendto(_sock, (const void *) &data, sizeof(data), 0,
        reinterpret_cast<const sockaddr *>(&dst), sizeof(dst));
    }

void Babel::VoIpNetwork::VoIpClient::recvOtherClientData()
{


    sockaddr_in recvaddr{};
    socklen_t recvlen = sizeof(sockaddr_in);
    recvfrom(_sock, &_otherClientData, sizeof(_otherClientData), 0, reinterpret_cast<sockaddr *>(&recvaddr), &recvlen);

    std::cout << "exit" << std::endl;
}

void Babel::VoIpNetwork::VoIpClient::startTransmition()
{
    int flags = fcntl(_sock,F_GETFL,0);
    if (flags == -1)
        throw std::runtime_error(std::strerror(errno));
    fcntl(_sock, F_SETFL, flags | O_NONBLOCK);

    _runnig = true;
    _sendThread = std::thread(&VoIpClient::sendLoop, this);
    _recvThread = std::thread(&VoIpClient::recvLoop, this);
}

void Babel::VoIpNetwork::VoIpClient::sendLoop()
{
    while (_runnig) {
        feedSendBuffer();
        sendto(_sock, _sendBuff, _sendBuffLen, 0, reinterpret_cast<const sockaddr *>(&_otherClientData),
            sizeof(_otherClientData));
    }
}

void Babel::VoIpNetwork::VoIpClient::recvLoop()
{
    char buff[200];
    struct sockaddr_in fromAddr{};
    socklen_t len = sizeof(fromAddr);
    int ret = 0;

    while (_runnig) {
        ret = _recvBuffLen = recvfrom(_sock, _recvBuff, MAX_RECV_BUFF_LEN, 0, reinterpret_cast<sockaddr *>(&fromAddr), &len);
        if (ret == -1)
            continue;
        prossesRecvData();
    }
}

void Babel::VoIpNetwork::VoIpClient::stop()
{
    _runnig = false;
    _sendThread.detach();
    _recvThread.detach();
}

// Replace by code
void Babel::VoIpNetwork::VoIpClient::feedSendBuffer()
{
    usleep(10000);
    auto t = std::time(nullptr);
    _sendBuffLen = sizeof(t);
    std::memcpy(_sendBuff, &t, _sendBuffLen);
}

void Babel::VoIpNetwork::VoIpClient::prossesRecvData()
{
    std::cout << "size: " << _recvBuffLen << std::endl;
    std::cout << _recvBuff << std::endl;
}

Babel::VoIpNetwork::VoIpClient::~VoIpClient()
{
    close(_sock);
}
