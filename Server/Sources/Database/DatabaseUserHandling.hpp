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

namespace Babel
{
namespace Database
{
class DatabaseUserHandling
{
public:
	/**
		 * Constructor : Take a database pointer to interact the table
		 */
	DatabaseUserHandling(std::shared_ptr<Db> database);
	/**
		 * Destructor
		 */
	~DatabaseUserHandling();

	/**
	 * Create the User table if not exist
	 */
	void createTable();
	/**
	 * Add user to the table User
	 * @param username Username of the user to add
	 * @param password Password of the user to add
	 */
	void addUser(const std::string &username, const std::string &password);
	/**
	 * Delete user from the table User
	 * @param user ID of the user to delete
	 */
	void deleteUser(const int &user);
	/**
	 * Check if user exist in user db
	 * @param username Username of user to find
	 * @param password Password of user to find
	 * @return client id
	 */
	int userExists(const std::string &username, const std::string &password);
	/**
	 * Check if user exist in user db
	 * @param username Username of user to find
	 * @return client id
	 */
	int userExists(const std::string &username);

	/**
	 * Get username by ID user
	 * @param user ID of the user
	 */
	std::string getUsername(const int &user);
	/**
	 * WIP
	 */
	void getUserInfos(const int &user);

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

#endif /* !DATABASEUSERHANDLING_HPP_ */
