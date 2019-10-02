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
#include <vector>
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
	 * Get all the friend request of a user
	 * @param ID client to find all friend request of
	 * @return all ID of user who sent a friend request to the user id in parameters
	 */
	std::vector<int> getAllFriendsRequest(const int &id);
	/**
	 * Change status of a frienship to accepted
	 * @param id1 ID of the first friend
	 * @param id2 ID of the second friend
	 */
	void acceptFriendRequest(const int &id1, const int &id2);
	/**
	 * Delete a friend request
	 * @param id1 ID of the first friend
	 * @param id2 ID of the second friend
	 */
	void rejectFriendRequest(const int &id1, const int &id2);

	/**
	 * Get ID of a friendship
	 * @param id1 ID of the first friend
	 * @param id2 ID of the second friend
	 */
	int getFriendShipID(const int &id1, const int &id2);
	/**
		 * Get infos about a friendship (WIP)
		 * @param id ID of the frienship
		 */
	void getFriendShipInfos(const int &id);
	/**
		 * Get all friends of a user (WIP)
		 * @param user ID of the user
		 */
	std::vector<int> getAllFriendsOf(const int &user);

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