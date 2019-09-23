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

class DatabaseUserDiscussionHandling {
	public:
		DatabaseUserDiscussionHandling(std::shared_ptr<Db> database);
		~DatabaseUserDiscussionHandling();

        void createTable();
        void addUserDiscussion(const int &user, const int discussion);
        void deleteUserDiscussion(const int &user);

        void getUserList(const int &discussion);
        void getDiscussionList(const int &user);

	protected:
	private:
        /*int createCallback(void *notUsed, int argc, char **argv, char **azColName);
		int addCallback(void *notUsed, int argc, char **argv, char **azColName);
		int deleteCallback(void *notUsed, int argc, char **argv, char **azColName);

		int selectAllCallback(void *notUsed, int argc, char **argv, char **azColName);
		int selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName);*/

		std::shared_ptr<Db> _database;
};

#endif /* !DATABASEUSERDISCUSSIONHANDLING_HPP_ */