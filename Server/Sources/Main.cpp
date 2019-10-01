/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Main
*/

#include "NetworkClient.hpp"
#include "User.hpp"
#include "MainServer.hpp"
#include "DatabaseMessageHandling.hpp"
#include "DatabaseDiscussionHandling.hpp"
#include "DatabaseUserDiscussionHandling.hpp"
#include "DatabaseUserHandling.hpp"
#include "DatabaseUserFriendHandling.hpp"

int main(int ac, char **av)
{
    Babel::Network::MainServer<User> mainServer(1337);

    mainServer.run();

    return 0;
}