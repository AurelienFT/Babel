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

class DatabaseDiscussionHandling {
	public:
		DatabaseDiscussionHandling(std::shared_ptr<Db> database);
		~DatabaseDiscussionHandling();

                void createTable();
                void addDiscussion(const std::string &discussionName);
                void deleteDiscussion(const int &discussion);

                void getDiscussionInfos(const int &discussion);

	protected:
	private:
                /*int createCallback(void *notUsed, int argc, char **argv, char **azColName);
                int addCallback(void *notUsed, int argc, char **argv, char **azColName);
                int deleteCallback(void *notUsed, int argc, char **argv, char **azColName);

                int selectAllCallback(void *notUsed, int argc, char **argv, char **azColName);
                int selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName);*/

                std::shared_ptr<Db> _database;
};

#endif /* !DATABASEDISCUSSIONHANDLING_HPP_ */