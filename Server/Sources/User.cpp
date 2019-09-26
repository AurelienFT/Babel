/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** User
*/

#include "User.hpp"
#include <iostream>
#include <cstring>

std::vector<User> User::getFriends()
{
	
}

void User::onMessage(std::vector<uint8_t> &buff)
{
    printf("Message: %d {", _fd);
    for (auto i : buff) {
        printf("%x", i);
    }
    printf("}\n");
}

User::User(int fd, struct sockaddr_in *sockaddrIn)
	: 	Babel::Network::NetworkClient(fd, sockaddrIn)
{
    std::cout << "New network client, id: " << _fd << std::endl;
}

User::~User()
{
    std::cout << "Network client " << _fd  << "disconnected" << std::endl;
}
