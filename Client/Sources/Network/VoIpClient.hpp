//
// Created by theo.zapata on 10/4/19.
//

#ifndef BABEL_VOIPCLIENT_HPP
#define BABEL_VOIPCLIENT_HPP

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>


namespace Babel {
    namespace VoIpNetwork {

        class VoIpClient {
        private:

            int _sock = -1;
            int _port;

            struct sockaddr_in _otherClientData{};

            std::atomic_bool _runnig;
            std::thread _sendThread{};
            std::thread _recvThread{};

            void sendLoop();
            void recvLoop();
        protected:
            static const int MAX_SEND_BUFF_LEN = 512;
            size_t _sendBuffLen = 0;
            uint8_t _sendBuff[MAX_SEND_BUFF_LEN];

            static const int MAX_RECV_BUFF_LEN = 512;
            size_t _recvBuffLen = 0;
            uint8_t _recvBuff[MAX_RECV_BUFF_LEN];

            virtual void feedSendBuffer();
            virtual void prossesRecvData();

        public:
            VoIpClient(const std::string &ip, int port);
            void recvOtherClientData();
            void startTransmition();
            void stop();
            virtual ~VoIpClient();
        };
    }
}
#endif //BABEL_VOIPCLIENT_HPP
