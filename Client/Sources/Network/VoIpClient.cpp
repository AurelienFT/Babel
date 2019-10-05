//
// Created by theo.zapata on 10/4/19.
//

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <opus.h>

#include "Server/Sources/Network/VoIp.hpp"
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
    OpusEncoder* enc = opus_encoder_create(SAMPLE_RATE, NUM_CHANNELS, OPUS_APPLICATION_VOIP, &err);

    _audio.Record();

	while (_audio.isRecording()) {
		if (_audio.getSendStatus()) {

			data = _audio.getAudioData().recordedSamples;

			unsigned char temp[SIZE_FLOAT_ARRAY / ENCODE_NUMBER];
			int total = 0;

			for (auto i = 0; i < ENCODE_NUMBER; i++) {
				
				_sendBuff.cuts[i] = total;
				int size = opus_encode_float(enc, data + (ENCODE_RATE *i), ENCODE_RATE, temp, 4000);
				
				for (auto j = 0; j < size; j++, total++) {
					_sendBuff.data[total] = temp[j];
				}
			}
			_sendBuff.cuts[ENCODE_NUMBER] = total;
            _sendBuffLen = sizeof(_sendBuff);
            sendto(_sock, &_sendBuff, _sendBuffLen, 0, reinterpret_cast<const sockaddr *>(&_otherClientData),
            sizeof(_otherClientData));

			_audio.resetSendStatus();
		}
		Pa_Sleep(100);
	}
}

void Babel::VoIpNetwork::VoIpClient::prossesRecvData()
{
    struct sockaddr_in fromAddr{};
    socklen_t len = sizeof(fromAddr);
    int ret = 0;
    int err = 0;

    float data[SIZE_FLOAT_ARRAY * sizeof(float)];
	OpusDecoder *rec = opus_decoder_create(SAMPLE_RATE, NUM_CHANNELS, &err);

	_audio.Listen();
	while (_audio.isListening())
	{

		if (_audio.getRecvStatus()) {
			_audio.resetAudioData();
            int tmp1 = recvfrom(_sock, (char*)&_recvBuff, MAX_RECV_BUFF_LEN, 0, reinterpret_cast<sockaddr *>(&fromAddr), &len);
            if (tmp1 < sizeof(sendData)) {
                continue;
            }
            if (tmp1 == -1) {
                continue;
            }
			float tmp[160];
			for (auto i = 0; i < ENCODE_NUMBER; i++) {
				opus_decode_float(rec, _recvBuff.data + _recvBuff.cuts[i], _recvBuff.cuts[i + 1] - _recvBuff.cuts[i], tmp, ENCODE_RATE, 0);
				
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
    close(_sock);
}
