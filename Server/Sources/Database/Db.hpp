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

namespace Babel
{
namespace Database
{
class Db
{
public:
    /**
         * Constructor : Connect to db with sqlite3
         */
    Db()
    {
        int err = 0;

        err = sqlite3_open("messages.db", &_database);

        if (err)
        {
            //error
            exit(84);
        }

        if (sqlite3_exec(_database, "PRAGMA foreign_keys = ON;", NULL, NULL, 0))
        {
            std::cout << "DB Error: " << sqlite3_errmsg(_database) << std::endl;
            exit(0);
        }
    };
    /**
         * Destructor
         */
    ~Db()
    {
        sqlite3_close(_database);
    };
    /**
         * Execute a sqlRequest on the db
         * @param sqlRequest SQL Request to execute
         * @param callback callback called by sqlite3 wehn the SQL request is execute
         * @param data Data filled in the callback
         * @param errorMessage Filled by sqlite3 if a error happen
         */
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
} // namespace Database
} // namespace Babel

#endif /* !DB_HPP_ */