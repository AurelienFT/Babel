/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseUserHandling
*/

#ifndef DATABASEUSERHANDLING_HPP_
#define DATABASEUSERHANDLING_HPP_

#include <memory>
#include <string>

#include "Db.hpp"

class DatabaseUserHandling {
	public:
		DatabaseUserHandling(std::shared_ptr<Db> database);
		~DatabaseUserHandling();

        void createTable();
        void addUser(const std::string &userName);//TO ADD multiple infos on the user (to see with everyone)
        void deleteUser(const int &user);

        void getUserInfos(const int &user);

	protected:
	private:
		/*int createCallback(void *notUsed, int argc, char **argv, char **azColName);
		int addCallback(void *notUsed, int argc, char **argv, char **azColName);
		int deleteCallback(void *notUsed, int argc, char **argv, char **azColName);

		int selectAllCallback(void *notUsed, int argc, char **argv, char **azColName);
		int selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName);*/

		std::shared_ptr<Db> _database;
};

#endif /* !DATABASEUSERHANDLING_HPP_ */