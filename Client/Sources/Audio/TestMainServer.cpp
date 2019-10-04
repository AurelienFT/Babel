/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** TestMain
*/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <opus.h>
#include "Audio.hpp"
#define PORT 8080

int main(int ac, char **av)
{
	Audio audio;
	audioData temp;
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr,
		sizeof(servaddr)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	float data[SIZE_FLOAT_ARRAY * sizeof(float)];
	int err = 0;
	OpusDecoder *rec = opus_decoder_create(SAMPLE_RATE, NUM_CHANNELS, &err);

	audio.Listen();
	while (audio.isListening())
	{
		if (audio.getRecvStatus()) {
			sendData recved;
			audio.resetAudioData();
			recv(sockfd, &recved, sizeof(recved), MSG_WAITALL);

			float tmp[160];
			for (auto i = 0; i < 100; i++) {
				opus_decode_float(rec, recved.data + recved.cuts[i], recved.cuts[i + 1] - recved.cuts[i], tmp, 80, 0);
				
				for (auto j = 0; j < 160; j++) {
					data[j + i * 80] = tmp[j];
				}
			}
			audio.addAudioData(data, 0);
			audio.resetRecvStatus();
		}
		Pa_Sleep(100);
	}

	return 0;
}