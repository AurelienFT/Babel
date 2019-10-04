/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** TestMain
*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cerrno>
#include <cstring>
#include <opus.h>
#include <iostream>
#include "Audio.hpp"
#define PORT 8080

int main(int argc, char const *argv[])
{
	Audio audio, audio1;
	int sockfd;
	char *hello = "Hello from client";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int err = 0;
	float *data;
	OpusEncoder* enc = opus_encoder_create(8000, NUM_CHANNELS, OPUS_APPLICATION_VOIP, &err);

	audio.Record();

	while (audio.isRecording()) {
		if (audio.getSendStatus()) {

			data = audio.getAudioData().recordedSamples;

			sendData toSend;
			unsigned char temp[SIZE_FLOAT_ARRAY / 100];
			int total = 0;

			for (auto i = 0; i < 100; i++) {
				
				toSend.cuts[i] = total;
				int size = opus_encode_float(enc, data + (80 *i), 80, temp, 4000);
				
				for (auto j = 0; j < size; j++, total++) {
					toSend.data[total] = temp[j];
				}
			}
			toSend.cuts[100] = total;
			
			if (sendto(sockfd, &toSend, sizeof(toSend), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
				std::cout <<std::strerror(errno) <<std::endl;
			audio.resetSendStatus();
		}
		Pa_Sleep(100);
	}

	return 0;
}