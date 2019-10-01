/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseMessageHandling
*/

#ifndef DATABASEMESSAGEHANDLING_HPP_
#define DATABASEMESSAGEHANDLING_HPP_

#include <memory>
#include <string>

#include "Db.hpp"
namespace Babel
{
namespace Database
{
class DatabaseMessageHandling
{
public:
        /**
                 * Constructor: Take the database pointer to interact with the Discussion table
                 * @param database Pointer to the database
                 */
        DatabaseMessageHandling(std::shared_ptr<Db> database);
        /**
                 * Destructor
                 */
        ~DatabaseMessageHandling();

        /**
                 * Create the Message table
                 */
        void createTable();
        /**
                 * Enter a message in the Message table
                 * @param sender Sender ID
                 * @param group Group ID
                 * @param messageData Content of the message
                 */
        void addMessage(const int &sender, const int &group, const std::string &messageData);
        /**
                 * Delete a message in the Message table
                 * @param messageId ID of the message
                 */
        void deleteMessage(const int &messageId);

        /**
                 * Get all message of a group (WIP)
                 * @param group Group ID of the message
                 */
        void getAllMessage(const int &group);
        /**
                 * Get a range of messages of a group (WIP)
                 * @param group Group ID of the message
                 * @param numberOfMessage number of message to get
                 */
        void getRangeMessage(const int &group, const int &numberOfMessage);

protected:
private:
        /*int createCallback(void *notUsed, int argc, char **argv, char **azColName);
                int addCallback(void *notUsed, int argc, char **argv, char **azColName);
                int deleteCallback(void *notUsed, int argc, char **argv, char **azColName);

                int selectAllCallback(void *notUsed, int argc, char **argv, char **azColName);
                int selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName);*/

        std::shared_ptr<Babel::Database::Db> _database;
};
} // namespace Database
} // namespace Babel

#endif /* !DATABASEMESSAGEHANDLING_HPP_ */