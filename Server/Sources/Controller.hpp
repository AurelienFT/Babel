/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Controller
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <memory>
#include <vector>
#include <iostream>
#include <functional>
#include <NetworkInterface.hpp>
#include <DatabaseUserFriendHandling.hpp>
#include <DatabaseDiscussionHandling.hpp>
#include <DatabaseMessageHandling.hpp>
#include <DatabaseUserHandling.hpp>
#include <Db.hpp>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream> 
#include <iterator>
template <typename T>
class Controller {
	public:
		/**
		 * Constructor : Initialize all classes to interact with database
		 * and create all functions which handle requests though the socket
		 */
		Controller() : _dbDiscussionHandling(_db), _dbMessageHandling(_db), _dbUserFriendHandling(_db), _dbUserHandling(_db) {
			_dbDiscussionHandling.createTable();
			_dbUserHandling.createTable();
			_dbUserFriendHandling.createTable();
			_dbMessageHandling.createTable();
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->registerUser(client, size, data); });
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->loginUser(client, size, data); });
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->createFriendRequest(client, size, data); });
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->updateData(client, size, data); });
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->acceptFriendRequest(client, size, data); });
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->rejectFriendRequest(client, size, data); });
		};
		/**
   		* Function to handle all messages and call the appropriate function
		* @param client The client object with all informations needed
		* @param messageType Type of message sended by client
		* @param payload Rest of the data of the packet with contains the buffer and his size
   		* @return MessageType
   		*/
		MessageType manageReponse(std::shared_ptr<T> client, MessageType messageType, char *payload) {
			int size = *(int *)payload;
			std::cout << "int = " << size << std::endl;
			MessageType type = controllerFunctions.at(static_cast<int>(messageType))(client, size, payload + 4);
			return type;
		};
		~Controller() {

		};
		std::string getReponse() const {
			return (_reponse);
		}
		void resetReponse() {
			_reponse = std::string("");
		}
	protected:
	private:
	  	MessageType registerUser(std::shared_ptr<T> client, size_t size, const char *data) {
			char tmp[size + 1] = {0};
			memcpy(tmp, data, size);
			std::string payload(tmp);
			std::string username = payload.substr(0, payload.find('|'));
			std::string password = payload.substr(payload.find('|') + 1, payload.length());
			_dbUserHandling.addUser(username, password);
			return MessageType::OK;
		};

	  	MessageType loginUser(std::shared_ptr<T> client, size_t size, const char *data) {
			char tmp[size + 1] = {0};
			memcpy(tmp, data, size);
			std::string payload(tmp);
			std::string username = payload.substr(0, payload.find('|'));
			std::string password = payload.substr(payload.find('|') + 1, payload.length());
			int id = _dbUserHandling.userExists(username, password);
			if (id == -1)
				return MessageType::ERROR_LOGIN;
			client->login(id);
			return MessageType::OK;
		};
		MessageType createFriendRequest(std::shared_ptr<T> client, size_t size, const char *data) {
			char tmp[size + 1] = {0};
			memcpy(tmp, data, size);
			std::string friendName(tmp);
			int id = client->getID();
			int idTwo = _dbUserHandling.userExists(friendName);
			if (idTwo == -1)
				return MessageType::ERROR_ADD_FRIEND;
			if (_dbUserFriendHandling.getFriendShipID(id, idTwo) != -1)
				return MessageType::ERROR_ADD_FRIEND;
			_dbUserFriendHandling.addFriendShip(id, idTwo, false);
			return MessageType::OK;
		};
		MessageType updateData(std::shared_ptr<T> client, size_t size, const char *data) {
			_reponse = std::string("");
			std::ostringstream vts;
			std::vector<std::string> friendsRequestUsers;
			std::vector<int> idsFriendsRequestUsers = _dbUserFriendHandling.getAllFriendsRequest(client->getID());
			for (auto idFriendsRequestUser : idsFriendsRequestUsers) {
				friendsRequestUsers.push_back(_dbUserHandling.getUsername(idFriendsRequestUser));
			}
 			if (!friendsRequestUsers.empty()) { 
				std::copy(friendsRequestUsers.begin(), friendsRequestUsers.end()-1, 
        			std::ostream_iterator<std::string>(vts, ",")); 
				vts << friendsRequestUsers.back(); 
	  			_reponse += vts.str();
			}
			_reponse += ";";
			std::vector<int> friendsIDs = _dbUserFriendHandling.getAllFriendsOf(client->getID());
			std::vector<std::string> friends;
			for (auto friendID : friendsIDs) {
				friends.push_back(_dbUserHandling.getUsername(friendID));
			}
			if (!friends.empty()) { 
				std::copy(friends.begin(), friends.end()-1, 
        			std::ostream_iterator<std::string>(vts, ",")); 
				vts << friends.back(); 
				_reponse += vts.str();
			}
			return MessageType::OK;
		};
		MessageType acceptFriendRequest(std::shared_ptr<T> client, size_t size, const char *data) {
			char tmp[size + 1] = {0};
			memcpy(tmp, data, size);
			std::string friendName(tmp);
			_dbUserFriendHandling.acceptFriendRequest(_dbUserHandling.userExists(friendName), client->getID());
			return MessageType::OK;
		};
		MessageType rejectFriendRequest(std::shared_ptr<T> client, size_t size, const char *data) {
			char tmp[size + 1] = {0};
			memcpy(tmp, data, size);
			std::string friendName(tmp);
			_dbUserFriendHandling.rejectFriendRequest( _dbUserHandling.userExists(friendName), client->getID());
			return MessageType::OK;
		}
		std::shared_ptr<Babel::Database::Db> _db = std::shared_ptr<Babel::Database::Db>(new Babel::Database::Db());
		Babel::Database::DatabaseDiscussionHandling _dbDiscussionHandling;
		Babel::Database::DatabaseMessageHandling _dbMessageHandling;
		Babel::Database::DatabaseUserFriendHandling _dbUserFriendHandling;
		Babel::Database::DatabaseUserHandling _dbUserHandling;
		std::vector<std::function<MessageType (std::shared_ptr<T>, size_t, const char *)>> controllerFunctions;
		std::string _reponse;
};

#endif /* !CONTROLLER_HPP_ */
