//
// Created by theo.zapata on 10/4/19.
//

#include <iostream>
#include "NetworkClient.hpp"
#include "VoIpClient.hpp"

int main()
{
    int port = 0;

    std::cin >> port;
    Babel::VoIpNetwork::VoIpClient client("127.0.0.1", port);

    client.recvOtherClientData();
    client.startTransmition();

    int a;
    std::cin >> a;

    client.stop();
}