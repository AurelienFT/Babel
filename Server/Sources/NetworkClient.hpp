//
// Created by theo.zapata on 9/16/19.
//

#ifndef CPP_BABEL_2019_NETWORKCLIENT_HPP
#define CPP_BABEL_2019_NETWORKCLIENT_HPP


#include <netinet/in.h>
#include <array>
#include <vector>

namespace Babel {
    namespace Network {

        class NetworkClient {
        public:
            int _fd;
            //Network
            struct sockaddr_in sockaddrInClient{};
            int sockaddrInClientLen = sizeof(sockaddrInClient);

            NetworkClient(int fd, struct sockaddr_in *sockaddrIn);
            virtual ~NetworkClient();
            void onMessage(std::vector<uint8_t> &buff);
        };
    }
}

#endif //CPP_BABEL_2019_NETWORKCLIENT_HPP
