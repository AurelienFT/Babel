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

class DatabaseUserFriendHandling {
	public:
		DatabaseUserFriendHandling(std::shared_ptr<Db> database);
		~DatabaseUserFriendHandling();

		void createTable();
		void addFriendShip(const int &first, const int &second, const bool &isAccepted);
		void deleteFirendShip(const int &id);

		void getFriendShipInfos(const int &id);
		void getAllFriendsOf(const int &user);

	protected:
	private:
		/*int createCallback(void *notUsed, int argc, char **argv, char **azColName);
		int addCallback(void *notUsed, int argc, char **argv, char **azColName);
		int deleteCallback(void *notUsed, int argc, char **argv, char **azColName);

		int selectAllCallback(void *notUsed, int argc, char **argv, char **azColName);
		int selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName);*/

		std::shared_ptr<Db> _database;
};

#endif /* !DATABASEUSERFRIENDHANDLING_HPP_ */