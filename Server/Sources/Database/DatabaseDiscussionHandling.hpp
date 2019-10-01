/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseDiscussionHandling
*/

#ifndef DATABASEDISCUSSIONHANDLING_HPP_
#define DATABASEDISCUSSIONHANDLING_HPP_

#include <memory>
#include <string>

#include "Db.hpp"

namespace Babel
{
namespace Database
{
class DatabaseDiscussionHandling
{
public:
        /**
                 * Constructor: Take the database pointer to interact with the Discussion table
                 * @param database Pointer to the database
                 */
        DatabaseDiscussionHandling(std::shared_ptr<Db> database);
        /**
                 * Destructor
                 */
        ~DatabaseDiscussionHandling();

        /**
                 * Create the Discussion table if not exist
                 */
        void createTable();
        /**
                 * Insert a discussion in the Discussion table
                 * @param discussionName discussion name to add
                 */
        void addDiscussion(const std::string &discussionName);
        /**
                 * Remove a discussion from the Discussion table
                 * @param discussion the discussion id to delete
                 */
        void deleteDiscussion(const int &discussion);
        /**
                 * Get disucssions infos from Discussion table
                 * @param discussion client id
                 */
        void getDiscussionInfos(const int &discussion);

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

#endif /* !DATABASEDISCUSSIONHANDLING_HPP_ */