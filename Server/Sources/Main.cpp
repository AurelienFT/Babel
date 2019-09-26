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
    std::shared_ptr<Db> testDb = std::make_shared<Db>();
    DatabaseUserHandling testUser(testDb);

    testUser.createTable();
    testUser.addUser("Jean-Pierre");
    testUser.getUserInfos(1);
    testUser.deleteUser(1);
    testUser.addUser("Jean-Paul");
    testUser.addUser("Un mec chelou");
    testUser.getUserInfos(2);
    testUser.getUserInfos(3);

    DatabaseDiscussionHandling testDiscussion(testDb);
    testDiscussion.createTable();
    testDiscussion.addDiscussion("Jean-Paul et Jean-Pierre");
    testDiscussion.getDiscussionInfos(1);
    testDiscussion.deleteDiscussion(1);
    testDiscussion.addDiscussion("Jean-Pierre et Jean-Paul");
    testDiscussion.addDiscussion("Un mec chelou seul");
    testDiscussion.getDiscussionInfos(2);
    testDiscussion.getDiscussionInfos(3);

    DatabaseMessageHandling testMessage(testDb);
    testMessage.createDiscussion();
    testMessage.addMessage(2, 2, "Tiens, Tiens, Tiens...");
    testMessage.getAllMessage(1);
    testMessage.deleteMessage(1);
    testMessage.addMessage(3, 3, "Je suis Booba");
    testMessage.getAllMessage(1);

    DatabaseUserDiscussionHandling testUserDiscussion(testDb);
    testUserDiscussion.createTable();
    testUserDiscussion.addUserDiscussion(2, 2);
    testUserDiscussion.getDiscussionList(2);
    testUserDiscussion.getUserList(2);
    testUserDiscussion.deleteUserDiscussion(1);
    testUserDiscussion.addUserDiscussion(3, 3);
    testUserDiscussion.getUserList(3);
    testUserDiscussion.getDiscussionList(3);

    DatabaseUserFriendHandling testUserFriend(testDb);
    testUserFriend.createTable();
    testUserFriend.addFriendShip(2, 2, false);
    testUserFriend.getAllFriendsOf(2);
    testUserFriend.getFriendShipInfos(1);
    testUserFriend.deleteFirendShip(1);
    testUserFriend.addFriendShip(2, 3, false);
    testUserFriend.addFriendShip(2, 3, true);
    testUserFriend.addFriendShip(3, 3, false);
    testUserFriend.getAllFriendsOf(2);
    testUser.deleteUser(2);
    testUserFriend.getAllFriendsOf(3);
    testUserFriend.addFriendShip(3, 3, true);
    testUserFriend.getAllFriendsOf(3);

    testUserDiscussion.getDiscussionList(3);

    return 0;
}