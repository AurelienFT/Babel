/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** TestMain
*/

#include "Audio.hpp"
#include <iostream>
#include <stdio.h>

int main(int ac, char **av)
{
	Audio audio;

	audio.Record();
	while (audio.isRecording());
	audio.Listen();
	while (audio.isListening());
	std::cout <<"end" <<std::endl;
}