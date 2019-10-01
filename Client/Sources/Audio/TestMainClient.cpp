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

	int n, len;
	float *data;

	audio.Record();

	while (audio.isRecording()) {
		if (audio.getSendStatus()) {
			data = audio.getAudioData().recordedSamples;
			sendto(sockfd, data, SIZE_FLOAT_ARRAY, MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
			audio.resetSendStatus();
		}
		Pa_Sleep(100);
	}

	return 0;
}