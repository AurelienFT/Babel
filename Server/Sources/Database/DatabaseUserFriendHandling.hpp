/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseUserFriendHandling
*/

#ifndef DATABASEUSERFRIENDHANDLING_HPP_
#define DATABASEUSERFRIENDHANDLING_HPP_

#include <memory>
#include <string>

#include "Db.hpp"

namespace Babel
{
namespace Database
{
class DatabaseUserFriendHandling
{
public:
	/**
		 * Constructor : Take a database pointer to interact with the table
		 * @param database Pointer to the database
		 */
	DatabaseUserFriendHandling(std::shared_ptr<Db> database);
	/**
		 * Destructor
		 */
	~DatabaseUserFriendHandling();

	/**
		 * Create a table UserFriend in the database
		 */
	void createTable();
	/**
		 * Add a friendship between two users
		 * @param first First user ID
		 * @param second Second user ID
		 * @param isAccepted Friend request is accepted by the second user
		 */
	void addFriendShip(const int &first, const int &second, const bool &isAccepted);
	/**
		 * Delete a friendship
		 * @param id ID of the friendship to delete
		 */
	void deleteFriendShip(const int &id);
	/**
		 * Get infos about a friendship (WIP)
		 * @param id ID of the frienship
		 */
	void getFriendShipInfos(const int &id);
	/**
		 * Get all friends of a user
		 * @param user ID of the user
		 */
	void getAllFriendsOf(const int &user);

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

#endif /* !DATABASEUSERFRIENDHANDLING_HPP_ */