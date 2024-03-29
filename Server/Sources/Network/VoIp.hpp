//
// Created by theo.zapata on 10/1/19.
//

#ifndef BABEL_VOIP_HPP
#define BABEL_VOIP_HPP
#ifdef __linux__
	#include <netinet/in.h>
#endif
#include <thread>
#include <atomic>

namespace Babel {
    namespace VoIpNetwork {

        enum VOIP_CODE : uint8_t {
            NEW_VOIP_CLIENT_CONNECTED = 'A',
        };

        class VoIp {
        private:

            static const int VOIP_MAX_CLIENT_NUMBER = 2;
            static const int REDONDANCE_SENDING = 10;
            int clientNumber = 0;

            std::atomic_bool _runnig;
            std::thread netLoop{};

            int _sock = 0;

#ifdef __linux__
            struct sockaddr_in sockAddrInClientList[VOIP_MAX_CLIENT_NUMBER] = {};
            socklen_t sockAddrInClientLenList[VOIP_MAX_CLIENT_NUMBER] = {sizeof(*sockAddrInClientList)};
#endif

            void threadLoop();
#ifdef __linux__
            bool isNewClient(const struct sockaddr_in *newClient, socklen_t newClientLen);
            void addClient(const struct sockaddr_in *newClient, socklen_t newClientLen);
#endif
            void sendDialingDataToClient();
        public:
            explicit VoIp();
            void run();
            void stop();
            int getPort();
        };

    }
}

#endif //BABEL_VOIP_HPP
