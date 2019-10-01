/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseUserDiscussionHandling
*/

#include "DatabaseUserDiscussionHandling.hpp"

Babel::Database::DatabaseUserDiscussionHandling::DatabaseUserDiscussionHandling(std::shared_ptr<Db> database)
    : _database(database)
{
    //createDiscussion();
}

Babel::Database::DatabaseUserDiscussionHandling::~DatabaseUserDiscussionHandling()
{
}

int createCallback2(void *notUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

void Babel::Database::DatabaseUserDiscussionHandling::createTable()
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("CREATE TABLE IF NOT EXISTS USER_DISCUSSION (") +
                    std::string("ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, ") +
                    std::string("USER INTEGER NOT NULL, ") +
                    std::string("DISCUSSION INTEGER NOT NULL, ") +
                    std::string("SENDDATE DATE NOT NULL, ") +
                    std::string("FOREIGN KEY(USER) REFERENCES USERS(ID) ON DELETE CASCADE, ") + 
                    std::string("FOREIGN KEY(DISCUSSION) REFERENCES DISCUSSIONS(ID) ON DELETE CASCADE);");
    
    if (_database->exec(sqlRequest, createCallback2, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int addCallback2(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void Babel::Database::DatabaseUserDiscussionHandling::addUserDiscussion(const int &user, const int discussion)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("INSERT INTO USER_DISCUSSION ('USER', 'DISCUSSION', 'SENDDATE') VALUES (") +
                    std::string("'") + std::to_string(user) + std::string("','") + std::to_string(discussion) + std::string("',strftime('%s','now'));");

    if (_database->exec(sqlRequest, addCallback2, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int deleteCallback2(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void Babel::Database::DatabaseUserDiscussionHandling::deleteUserDiscussion(const int &user)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("DELETE FROM 'USER_DISCUSSION' WHERE ID = '") + std::to_string(user) + std::string("';");

    if (_database->exec(sqlRequest, deleteCallback2, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int selectAllCallback2(void *notUsed, int argc, char **argv, char **azColName)
{
    std::string data;

    for (auto i = 0; i < argc; i++) {
        data += azColName[i] + std::string(" ") + argv[i] + std::string("\n");
    }

    //Send data
    std::cout <<data <<std::endl;

    return 0;
}

void Babel::Database::DatabaseUserDiscussionHandling::getDiscussionList(const int &user)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT DISCUSSION FROM USER_DISCUSSION WHERE USER = ") + std::to_string(user) + std::string(";");

    if (_database->exec(sqlRequest, selectAllCallback2, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

void Babel::Database::DatabaseUserDiscussionHandling::getUserList(const int &discussion)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT USER FROM USER_DISCUSSION WHERE DISCUSSION = ") + std::to_string(discussion) + std::string(";");

    if (_database->exec(sqlRequest, selectAllCallback2, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}