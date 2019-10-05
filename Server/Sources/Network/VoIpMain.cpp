//
// Created by theo.zapata on 10/2/19.
//


#include <iostream>
#include "VoIp.hpp"

int main()
{
    Babel::VoIpNetwork::VoIp voIp;

    voIp.run();

    int a ;

    // GFet port and send it to client for connection
    std::cout << voIp.getPort();
    std::cin >> a;


    voIp.stop();
}