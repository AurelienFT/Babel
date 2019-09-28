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

class DatabaseMessageHandling {
	public:
		DatabaseMessageHandling(std::shared_ptr<Db> database);
		~DatabaseMessageHandling();

                void createTable();
                void addMessage(const int &sender, const int &group, const std::string &messageData);
                void deleteMessage(const int &messageId);

                void getAllMessage(const int &group);
                void getRangeMessage(const int &group, const int &numberOfMessage);

	protected:
	private:
                /*int createCallback(void *notUsed, int argc, char **argv, char **azColName);
                int addCallback(void *notUsed, int argc, char **argv, char **azColName);
                int deleteCallback(void *notUsed, int argc, char **argv, char **azColName);

                int selectAllCallback(void *notUsed, int argc, char **argv, char **azColName);
                int selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName);*/

                std::shared_ptr<Db> _database;
};

#endif /* !DATABASEMESSAGEHANDLING_HPP_ */