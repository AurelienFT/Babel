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
            /**
             * File descriptor of the socket of the client.
             */
            int fd;
            /**
             * Struct with all informations about socket
             */
            struct sockaddr_in sockaddrInClient{};
            /**
             * Size of sockaddrInClient
             */
            int sockaddrInClientLen = sizeof(sockaddrInClient);
            /**
             * Constructor: Initialize the sockaddr_in struct
             * @param fd socket fd
             * @param sockaddrIn socket structure to fill in constructor
             */
            NetworkClient(int fd, struct sockaddr_in *sockaddrIn);
            /**
             * Destructor
             */
            virtual ~NetworkClient();
        };
    }
}

#endif //CPP_BABEL_2019_NETWORKCLIENT_HPP
