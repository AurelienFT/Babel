/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseUserDiscussionHandling
*/

#ifndef DATABASEUSERDISCUSSIONHANDLING_HPP_
#define DATABASEUSERDISCUSSIONHANDLING_HPP_

#include <memory>
#include <string>

#include "Db.hpp"
namespace Babel
{
namespace Database
{
class DatabaseUserDiscussionHandling
{
public:
	/**
		 * Constructor : Take a database pointer to interact with the table
		 * @param database Pointer to the database
		 */
	DatabaseUserDiscussionHandling(std::shared_ptr<Db> database);
	/**
		 * Destructor
		 */
	~DatabaseUserDiscussionHandling();

	/**
	 * Create the User Discussion table if not exist
	 */
	void createTable();
	/**
	 * Add a User Discussion to the table
	 * @param user User ID
	 * @param discussion Discussion ID
	 */
	void addUserDiscussion(const int &user, const int discussion);
	/**
	 * Delete a User Discussion to the table
	 * @param user User ID
	 */
	void deleteUserDiscussion(const int &user);
	/**
	 * Get a list of all conversations of a user (WIP)
	 * @param discussion Discussion ID
	 */
	void getUserList(const int &discussion);
	/**
	 * Get a list of all discussions of a user (WIP)
	 * @param user User ID
	 */
	void getDiscussionList(const int &user);

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

#endif /* !DATABASEUSERDISCUSSIONHANDLING_HPP_ */