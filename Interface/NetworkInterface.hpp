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
	ACCEPT_FRIEND_REQUEST = 4,
	REJECT_FRIEND_REQUEST = 5,
	CALL = 6,
	ERROR_LOGIN = -1,
	ERROR_ADD_FRIEND = -2,
	ERROR_CALL = -3,
	OK = 127,
};

#endif