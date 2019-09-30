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

int User::getID() const {
    return _id;
}

void User::onMessage(std::vector<uint8_t> &buff)
{
    printf("Message: %d {", fd);
    for (auto i : buff) {
        printf("%x", i);
    }
    printf("}\n");
}

void User::login(int id)
{
    _id = id;
    _logged = true;
}

User::User(int fd, struct sockaddr_in *sockaddrIn)
	: 	Babel::Network::NetworkClient(fd, sockaddrIn)
{
    std::cout << "New network client, id: " << fd << std::endl;
}

User::~User()
{
    std::cout << "Network client " << fd  << "disconnected" << std::endl;
}
