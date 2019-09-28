/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseUserHandling
*/

#include "DatabaseUserHandling.hpp"

DatabaseUserHandling::DatabaseUserHandling(std::shared_ptr<Db> database)
    : _database(database)
{
}

DatabaseUserHandling::~DatabaseUserHandling()
{
}

int /*DatabaseUserHandling::*/createCallback3(void *notUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

void DatabaseUserHandling::createTable()
{
    std::string sqlRequest;
    std::string errorMessage = "";

    sqlRequest =    std::string("CREATE TABLE IF NOT EXISTS USERS (") +
                    std::string("ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, ") +
                    std::string("CREATIONDATE DATE NOT NULL, ") +
                    std::string("NAME TEXT NOT NULL, ") +
                    std::string("PASSWORD TEXT NOT NULL);");
    
    if (_database->exec(sqlRequest, createCallback3, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int /*DatabaseUserHandling::*/addCallback3(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void DatabaseUserHandling::addUser(const std::string &userName, const std::string &password)
{
    std::string sqlRequest;
    std::string errorMessage = "";

    sqlRequest =    std::string("INSERT INTO USERS ('CREATIONDATE', 'NAME', 'PASSWORD') VALUES (") +
                    std::string("strftime('%s','now'),'") + userName + std::string("','") + password + std::string("');");

    if (_database->exec(sqlRequest, addCallback3, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int /*DatabaseUserHandling::*/deleteCallback3(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void DatabaseUserHandling::deleteUser(const int &user)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("DELETE FROM 'USERS' WHERE ID = '") + std::to_string(user) + std::string("';");

    if (_database->exec(sqlRequest, deleteCallback3, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}


int /*DatabaseUserHandling::*/selectUserCallback3(void *id_to_fill, int argc, char **argv, char **azColName)
{
    int *id = (int *)id_to_fill;

    *id = std::atoi(argv[0]);
    // std::string data;

    // for (auto i = 0; i < argc; i++) {
    //     data += azColName[i] + std::string(" ") + argv[i] + std::string("\n");
    // }

    // //Send data
    // std::cout <<data <<std::endl;

    return 0;
}

int DatabaseUserHandling::userExists(const std::string &username, const std::string &password)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";
    int id = -1;
    sqlRequest = std::string("SELECT * FROM USERS WHERE NAME = '") + username + std::string("' AND PASSWORD = '") + password +  std::string("'");

    if (_database->exec(sqlRequest, selectUserCallback3, &id, errorMessage.c_str())) {
        //error message
        exit(0);
    }
    return (id);
}

int DatabaseUserHandling::getIDFromUsername(const std::string &username)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";
    int id = -1;
    sqlRequest = std::string("SELECT * FROM USERS WHERE NAME = '") + username + std::string("'");

    if (_database->exec(sqlRequest, selectUserCallback3, &id, errorMessage.c_str())) {
        //error message
        exit(0);
    }
    return (id);   
}

void DatabaseUserHandling::getUserInfos(const int &user)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM USERS WHERE ID = ") + std::to_string(user) + std::string(";");

    if (_database->exec(sqlRequest, selectUserCallback3, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}
