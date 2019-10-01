/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** DatabaseUserFriendHandling
*/

#include "DatabaseUserFriendHandling.hpp"

Babel::Database::DatabaseUserFriendHandling::DatabaseUserFriendHandling(std::shared_ptr<Db> database)
    : _database(database)
{
}

Babel::Database::DatabaseUserFriendHandling::~DatabaseUserFriendHandling()
{
}

int createCallback4(void *notUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

void Babel::Database::DatabaseUserFriendHandling::createTable()
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest =    std::string("CREATE TABLE IF NOT EXISTS USER_FRIENDSHIP (") +
                    std::string("ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, ") +
                    std::string("FIRST INTEGER NOT NULL, ") +
                    std::string("SECOND INTEGER NOT NULL, ") +
                    std::string("CREATIONDATE DATE NOT NULL, ") +
                    std::string("STATUS INTEGER NOT NULL, ") +
                    std::string("FOREIGN KEY(FIRST) REFERENCES USERS(ID) ON DELETE CASCADE, ") +
                    std::string("FOREIGN KEY(SECOND) REFERENCES USERS(ID) ON DELETE CASCADE);");
    
    if (_database->exec(sqlRequest, createCallback4, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int addCallback4(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void Babel::Database::DatabaseUserFriendHandling::addFriendShip(const int &first, const int &second, const bool &isAccepted)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    if (!isAccepted) {

        sqlRequest =    std::string("INSERT INTO USER_FRIENDSHIP ('FIRST', 'SECOND', 'CREATIONDATE', 'STATUS') VALUES (") +
                        std::string("'") + std::to_string(first) + std::string("','") + 
                        std::to_string(second) + std::string("',strftime('%s','now'), '0');");

    } else {

        sqlRequest =    std::string("UPDATE USER_FRIENDSHIP SET STATUS = '1' WHERE ((FIRST = ") + std::to_string(first) +
                        std::string(" OR SECOND = ") + std::to_string(first) + std::string(") AND (FIRST = " + std::to_string(second) + " OR SECOND = ") +
                        std::to_string(second) + std::string("));");
    }

    if (_database->exec(sqlRequest, addCallback4, 0, errorMessage.c_str())) {
            //error message
            exit(0);
        }
}

int deleteCallback4(void *notUsed, int argc, char **argv, char **azColName)
{
    //send that it's done
    return 0;
}

void Babel::Database::DatabaseUserFriendHandling::deleteFriendShip(const int &id)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("DELETE FROM 'USER_FRIENDSHIP' WHERE ID = '") + std::to_string(id) + std::string("';");

    if (_database->exec(sqlRequest, deleteCallback4, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

int selectAllCallback4(void *notUsed, int argc, char **argv, char **azColName)
{
    std::string data;

    for (auto i = 0; i < argc; i++) {
        data += azColName[i] + std::string(" ") + argv[i] + std::string("\n");
    }

    //Send data
    std::cout <<data <<std::endl;

    return 0;
}

void Babel::Database::DatabaseUserFriendHandling::getFriendShipInfos(const int &id)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM USER_FRIENDSHIP WHERE ID = ") + std::to_string(id) + std::string(";");

    if (_database->exec(sqlRequest, selectAllCallback4, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

void Babel::Database::DatabaseUserFriendHandling::getAllFriendsOf(const int &user)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM USER_FRIENDSHIP WHERE (FIRST = ") + std::to_string(user) +
    std::string(" OR SECOND = ") + std::to_string(user) + std::string(");");

    if (_database->exec(sqlRequest, selectAllCallback4, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}