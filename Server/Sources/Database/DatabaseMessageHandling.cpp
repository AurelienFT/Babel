/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseMessageHandling
*/

#include "DatabaseMessageHandling.hpp"

DatabaseMessageHandling::DatabaseMessageHandling(std::shared_ptr<Db> database)
    : _database(database)
{
    //createDiscussion();
}

DatabaseMessageHandling::~DatabaseMessageHandling()
{
}

int /*DatabaseMessageHandling::*/createCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

void DatabaseMessageHandling::createDiscussion()
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("CREATE TABLE MESSAGES (") +
                    std::string("ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ") +
                    std::string("SENDER INTEGER NOT NULL, ") +
                    std::string("DISCUSSION INTEGER NOT NULL, ") +
                    std::string("SENDDATE DATE NOT NULL, ") +
                    std::string("MESSAGE TEXT NOT NULL, ") +
                    std::string("FOREIGN KEY(SENDER) REFERENCES USERS(ID) ON DELETE CASCADE, ") +
                    std::string("FOREIGN KEY(DISCUSSION) REFERENCES DISCUSSIONS(ID) ON DELETE CASCADE);");
    
    if (_database->exec(sqlRequest, createCallback, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int /*DatabaseMessageHandling::*/addCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void DatabaseMessageHandling::addMessage(const int &sender, const int &group, const std::string &messageData)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("INSERT INTO MESSAGES ('SENDER', 'DISCUSSION', 'SENDDATE', 'MESSAGE') VALUES (") +
                    std::string("'") + std::to_string(sender) + std::string("','") + std::to_string(group) +
                    std::string("',strftime('%s','now'),'") + messageData + std::string("');");

    if (_database->exec(sqlRequest, addCallback, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int /*DatabaseMessageHandling::*/deleteCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void DatabaseMessageHandling::deleteMessage(const int &messageId)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("DELETE FROM 'MESSAGES' WHERE ID = '") + std::to_string(messageId) + std::string("';");

    if (_database->exec(sqlRequest, deleteCallback, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int /*DatabaseMessageHandling::*/selectAllCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    std::string data;

    for (auto i = 0; i < argc; i++) {
        data += azColName[i] + std::string(" ") + argv[i] + std::string("\n");
    }

    //Send data
    std::cout <<data <<std::endl;

    return 0;
}

void DatabaseMessageHandling::getAllMessage(const int &group)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM MESSAGES WHERE DISCUSSION = ") + std::to_string(group) + std::string(";");

    if (_database->exec(sqlRequest, selectAllCallback, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int /*DatabaseMessageHandling::*/selectRangeCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    std::string data;

    for (auto i = 0; i < argc; i++) {
        data += azColName[i] + std::string(" ") + argv[i] + std::string("\n");
    }

    //Send data
    std::cout <<data <<std::endl;

    return 0;
}

void DatabaseMessageHandling::getRangeMessage(const int &group, const int &numberOfMessage/*Peut-être date à la place*/)
{
    //LATER
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM MESSAGES WHERE DISCUSSION = ") + std::to_string(group) + std::string(";");
    //peut-être rajouter la date de dernier message voulu ?

    if (_database->exec(sqlRequest, selectRangeCallback, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}