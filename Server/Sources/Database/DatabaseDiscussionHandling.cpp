/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseDiscussionHandling
*/

#include "DatabaseDiscussionHandling.hpp"

Babel::Database::DatabaseDiscussionHandling::DatabaseDiscussionHandling(std::shared_ptr<Db> database)
    : _database(database)
{
}

Babel::Database::DatabaseDiscussionHandling::~DatabaseDiscussionHandling()
{
}

int createCallback1(void *notUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

void Babel::Database::DatabaseDiscussionHandling::createTable()
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("CREATE TABLE IF NOT EXISTS DISCUSSIONS (") +
                    std::string("ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, ") +
                    std::string("CREATIONDATE DATE NOT NULL, ") +
                    std::string("NAME TEXT NOT NULL);");
    
    if (_database->exec(sqlRequest, createCallback1, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int addCallback1(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void Babel::Database::DatabaseDiscussionHandling::addDiscussion(const std::string &discussionName)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("INSERT INTO DISCUSSIONS ('CREATIONDATE', 'NAME') VALUES (") +
                    std::string("strftime('%s','now'),'") + discussionName + std::string("');");

    if (_database->exec(sqlRequest, addCallback1, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int deleteCallback1(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void Babel::Database::DatabaseDiscussionHandling::deleteDiscussion(const int &discussion)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("DELETE FROM 'DISCUSSIONS' WHERE ID = '") + std::to_string(discussion) + std::string("';");

    if (_database->exec(sqlRequest, deleteCallback1, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int selectDiscussionCallback1(void *notUsed, int argc, char **argv, char **azColName)
{
    std::string data;

    for (auto i = 0; i < argc; i++) {
        data += azColName[i] + std::string(" ") + argv[i] + std::string("\n");
    }

    //Send data
    std::cout <<data <<std::endl;

    return 0;
}

void Babel::Database::DatabaseDiscussionHandling::getDiscussionInfos(const int &discussion)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM DISCUSSIONS WHERE ID = ") + std::to_string(discussion) + std::string(";");

    if (_database->exec(sqlRequest, selectDiscussionCallback1, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}