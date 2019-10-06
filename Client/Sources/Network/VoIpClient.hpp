//
// Created by theo.zapata on 10/4/19.
//

#ifndef BABEL_VOIPCLIENT_HPP
#define BABEL_VOIPCLIENT_HPP

#ifdef __linux__
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <strings.h>
#endif

#include <thread>

#include "Audio.hpp"

namespace Babel {
    namespace VoIpNetwork {

        class VoIpClient {
        private:

            int _sock = -1;
            int _port;

            Audio _audio;

#ifdef __linux__
            struct sockaddr_in _otherClientData{};
#endif

            std::atomic_bool _runnig;
            std::thread _sendThread{};
            std::thread _recvThread{};

            void sendLoop();
            void recvLoop();
        protected:
            static const int MAX_SEND_BUFF_LEN = 8000;
            size_t _sendBuffLen = 0;
            sendData _sendBuff;

            static const int MAX_RECV_BUFF_LEN = 20000;
            size_t _recvBuffLen = 0;
            sendData _recvBuff;

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
