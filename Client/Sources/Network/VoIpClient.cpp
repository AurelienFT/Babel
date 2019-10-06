//
// Created by theo.zapata on 10/4/19.
//

#include <string>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include "Encoding.hpp"
#include "Server/Sources/Network/VoIp.hpp"
#include "VoIpClient.hpp"

Babel::VoIpNetwork::VoIpClient::VoIpClient(const std::string &ip, int port) : _port(port)
{
	SOCKADDR_IN dst{};
    if (inet_pton(AF_INET, ip.c_str(), &dst.sin_addr) <= 0)
        throw std::runtime_error(std::strerror(errno));
	dst.sin_port = htons(_port);
    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock == -1)
        throw std::runtime_error(std::strerror(errno));
    uint8_t data = VOIP_CODE::NEW_VOIP_CLIENT_CONNECTED;
#ifdef __linux__
	sendto(_sock, (const void *) &data, sizeof(data), 0,
        reinterpret_cast<const sockaddr *>(&dst), sizeof(dst));
#endif
#ifdef _WIN64
	sendto(_sock, (const char *)&data, sizeof(data), 0,
		reinterpret_cast<const sockaddr *>(&dst), sizeof(dst));
#endif

}

void Babel::VoIpNetwork::VoIpClient::recvOtherClientData()
{
#ifdef __linux__
    sockaddr_in recvaddr{};
    socklen_t recvlen = sizeof(sockaddr_in);
    recvfrom(_sock, &_otherClientData, sizeof(_otherClientData), 0, reinterpret_cast<sockaddr *>(&recvaddr), &recvlen);
#endif

    std::cout << "exit" << std::endl;
}

void Babel::VoIpNetwork::VoIpClient::startTransmition()
{
#ifdef __linux__
    int flags = fcntl(_sock,F_GETFL,0);
    if (flags == -1)
        throw std::runtime_error(std::strerror(errno));
    fcntl(_sock, F_SETFL, flags | O_NONBLOCK);
#endif
    
    _runnig = true;
    _sendThread = std::thread(&VoIpClient::sendLoop, this);
    _recvThread = std::thread(&VoIpClient::recvLoop, this);
}

void Babel::VoIpNetwork::VoIpClient::sendLoop()
{
    while (_runnig) {
        feedSendBuffer();
    }
}

void Babel::VoIpNetwork::VoIpClient::recvLoop()
{
    while (_runnig) {
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
    float *data;
    int err;
    Babel::audio::Encoding enc;
    enc.encode_create(SAMPLE_RATE, NUM_CHANNELS, OPUS_APPLICATION_VOIP, &err);

    _audio.Record();

	while (_audio.isRecording()) {
		if (_audio.getSendStatus()) {

			data = _audio.getAudioData().recordedSamples;

			unsigned char temp[SIZE_FLOAT_ARRAY / ENCODE_NUMBER];
			int total = 0;

			for (auto i = 0; i < ENCODE_NUMBER; i++) {
				
				_sendBuff.cuts[i] = total;
				int size = enc.encode_float(data + (ENCODE_RATE *i), ENCODE_RATE, temp, SIZE_FLOAT_ARRAY / ENCODE_NUMBER);
				
				for (auto j = 0; j < size; j++, total++) {
					_sendBuff.data[total] = temp[j];
				}
			}
			_sendBuff.cuts[ENCODE_NUMBER] = total;
            _sendBuffLen = sizeof(_sendBuff);
#ifdef __linux__
            sendto(_sock, &_sendBuff, _sendBuffLen, 0, reinterpret_cast<const sockaddr *>(&_otherClientData),
            sizeof(_otherClientData));
#endif

			_audio.resetSendStatus();
		}
		Pa_Sleep(100);
	}
}

void Babel::VoIpNetwork::VoIpClient::prossesRecvData()
{
#ifdef __linux__
    struct sockaddr_in fromAddr{};
    socklen_t len = sizeof(fromAddr);
#endif
    int ret = 0;
    int err = 0;

    float data[SIZE_FLOAT_ARRAY * sizeof(float)];
	Babel::audio::Encoding dec;
    dec.decode_create(SAMPLE_RATE, NUM_CHANNELS, &err);

	_audio.Listen();
	while (_audio.isListening())
	{

		if (_audio.getRecvStatus()) {
			_audio.resetAudioData();
#ifdef __linux__
            int tmp1 = recvfrom(_sock, (char*)&_recvBuff, MAX_RECV_BUFF_LEN, 0, reinterpret_cast<sockaddr *>(&fromAddr), &len);
            if (tmp1 < sizeof(sendData)) {
                continue;
            }
            if (tmp1 == -1) {
                continue;
            }
#endif
			float tmp[160];
			for (auto i = 0; i < ENCODE_NUMBER; i++) {
				dec.decode_float(_recvBuff.data + _recvBuff.cuts[i], _recvBuff.cuts[i + 1] - _recvBuff.cuts[i], tmp, ENCODE_RATE, 0);
				
				for (auto j = 0; j < ENCODE_RATE * NUM_CHANNELS; j++) {
					data[j + i * ENCODE_RATE] = tmp[j];
				}
			}
			_audio.addAudioData(data, 0);
			_audio.resetRecvStatus();
		}
		Pa_Sleep(100);
	}
}

Babel::VoIpNetwork::VoIpClient::~VoIpClient()
{
#ifdef __linux__
    close(_sock);
#endif
}
