/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Main
*/

#include "DatabaseMessageHandling.hpp"

int main(int ac, char **av)
{
    DatabaseMessageHandling test(std::make_shared<Db>());

    //test.addMessage(1, 1, 2, "Tiens tiens tiens.");
    test.getRangeMessage(2, 1);

    return 0;
}