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
	audio.Listen();
	std::cout << "Test2" << std::endl;
}