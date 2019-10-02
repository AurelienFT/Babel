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

int unusedCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    return 0;
}

int selectAllIDFriendRequest(void *ids_to_fill, int argc, char **argv, char **azColName)
{
    std::vector<int> *ids = (std::vector<int> *) ids_to_fill;

    if (std::atoi(argv[4]) == 0)
        ids->push_back(std::atoi(argv[1]));
    return 0;
}

int selectAllIDFriend(void *ids_to_fill, int argc, char **argv, char **azColName)
{
    std::vector<int> *ids = (std::vector<int> *) ids_to_fill;

    if (std::atoi(argv[4]) == 1)
        ids->push_back(std::atoi(argv[1]));
    return 0;
}


std::vector<int> Babel::Database::DatabaseUserFriendHandling::getAllFriendsRequest(const int &id)
{
    std::string sqlRequest;
    std::string errorMessage = "";
    std::vector<int> ids;

    sqlRequest = std::string("SELECT * FROM USER_FRIENDSHIP WHERE SECOND = ") + std::to_string(id) + std::string(";");
    if (_database->exec(sqlRequest, selectAllIDFriendRequest, &ids, errorMessage.c_str())) {
        //error message
        exit(0);
    }
    return ids;
}

int selectAFriendShip(void *id_to_fill, int argc, char **argv, char **azColName)
{
    int *id = (int *) id_to_fill;

    *id = std::atoi(argv[0]);
    return 0;
}

int Babel::Database::DatabaseUserFriendHandling::getFriendShipID(const int &id1, const int &id2)
{
    std::string sqlRequest;
    std::string errorMessage = "";
    int id = -1;

    sqlRequest = std::string("SELECT * FROM USER_FRIENDSHIP WHERE FIRST = " + std::to_string(id1) + " AND SECOND = " + std::to_string(id2) + ";");
    if (_database->exec(sqlRequest, selectAFriendShip, &id, errorMessage.c_str())) {
        //error message
        exit(0);
    }
    return id;
}

void Babel::Database::DatabaseUserFriendHandling::acceptFriendRequest(const int &id1, const int &id2)
{
    std::string sqlRequest;
    std::string errorMessage = "";

    sqlRequest = std::string("UPDATE USER_FRIENDSHIP SET STATUS = 1 WHERE FIRST = " + std::to_string(id1) + " AND SECOND = " + std::to_string(id2) + ";");
    if (_database->exec(sqlRequest, unusedCallback, 0, errorMessage.c_str())) {
    }
    return;
}

void Babel::Database::DatabaseUserFriendHandling::rejectFriendRequest(const int &id1, const int &id2)
{
    std::string sqlRequest;
    std::string errorMessage = "";

    sqlRequest = std::string("DELETE FROM USER_FRIENDSHIP WHERE FIRST = " + std::to_string(id1) + " AND SECOND = " + std::to_string(id2) + ";");
    if (_database->exec(sqlRequest, unusedCallback, 0, errorMessage.c_str())) {
    }
    return;
}

void Babel::Database::DatabaseUserFriendHandling::getFriendShipInfos(const int &id)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";

    sqlRequest = std::string("SELECT * FROM USER_FRIENDSHIP WHERE ID = ") + std::to_string(id) + std::string(";");

    if (_database->exec(sqlRequest, unusedCallback, 0, errorMessage.c_str())) {
        //error message
        exit(0);
    }
}

std::vector<int> Babel::Database::DatabaseUserFriendHandling::getAllFriendsOf(const int &user)
{
    std::string sqlRequest;
    std::string errorMessage = "ouais";
    std::vector<int> ids;

    sqlRequest = std::string("SELECT * FROM USER_FRIENDSHIP WHERE FIRST = ") + std::to_string(user) +
    std::string(" OR SECOND = ") + std::to_string(user) + std::string(";");

    if (_database->exec(sqlRequest, selectAllIDFriend, &ids, errorMessage.c_str())) {
        //error message
        exit(0);
    }
    return ids;
}