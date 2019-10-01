/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** TestMain
*/

#include "Audio.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
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
	float data[SIZE_FLOAT_ARRAY];
	
	audio.Listen();
	while (audio.isListening())
	{
		if (audio.getRecvStatus()) {
			audio.resetAudioData();
			recv(sockfd, &data, SIZE_FLOAT_ARRAY, MSG_WAITALL);
			audio.addAudioData(data, 0);
			audio.resetRecvStatus();
		}
		Pa_Sleep(100);
	}

	return 0;
}