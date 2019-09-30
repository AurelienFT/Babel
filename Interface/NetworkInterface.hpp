/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** NetworkInterface
*/

#ifndef NETWORKINTERFACE_HPP_
#define NETWORKINTERFACE_HPP_

enum class MessageType : char
{
	REGISTER = 0,
	LOGIN = 1,
	ADD_FRIEND = 2,
	UPDATE_DATA = 3,
	ERROR_LOGIN = -1,
	ERROR_ADD_FRIEND = -2,
	OK = 127,
};

#endif