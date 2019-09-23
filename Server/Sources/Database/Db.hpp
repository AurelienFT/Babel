/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Db
*/

#ifndef DB_HPP_
#define DB_HPP_

#include <stdlib.h>

#include <iostream>

#include <sqlite3.h>

class Db {
	public:
		Db()
        {
                int err = 0;

                err = sqlite3_open("messages.db", &_database);

                if (err) {
                    //error
                    exit(84);
                }

                if (sqlite3_exec(_database, "PRAGMA foreign_keys = ON;", NULL, NULL, 0)) {
                    std::cout << "DB Error: " << sqlite3_errmsg(_database) << std::endl;
                    exit(0);
                }
        };

		~Db()
        {
            sqlite3_close(_database);
        };

        int exec(const std::string &sqlRequest, sqlite3_callback callback, void *data, const char *errorMessage)
        {
            if (sqlite3_exec(_database, sqlRequest.c_str(), callback, data, const_cast<char **>(&errorMessage)))
            {
                std::cout << "DB Error: " << sqlite3_errmsg(_database) << std::endl;
                return 1;
            }

            return 0;
        };

	protected:
	private:
        sqlite3 *_database;
};

#endif /* !DB_HPP_ */