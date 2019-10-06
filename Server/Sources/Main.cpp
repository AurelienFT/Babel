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
    try {
        Babel::Network::MainServer<User> mainServer(1337);

        mainServer.run();
        return 0;
    } catch (std::exception &e) {
        std::cerr << "Error in server " << std::endl;
        return (84);
    }
}