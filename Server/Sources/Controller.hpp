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
template <typename T>
class Controller {
	public:
		Controller() : _dbDiscussionHandling(_db), _dbMessageHandling(_db), _dbUserFriendHandling(_db), _dbUserHandling(_db) {
			_dbDiscussionHandling.createTable();
			_dbUserHandling.createTable();
			_dbUserFriendHandling.createTable();
			_dbMessageHandling.createTable();
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->registerUser(client, size, data); });
			controllerFunctions.push_back([this](std::shared_ptr<T> client, size_t size, const char *data) -> MessageType {return this->loginUser(client, size, data); });
		};
		MessageType manageReponse(std::shared_ptr<T> client, MessageType messageType, char *payload) {
			int size = *(int *)payload;
			std::cout << "int = " << size << std::endl;
			MessageType type = controllerFunctions.at(static_cast<int>(messageType))(client, size, payload + 4);
			return type;
		};
		~Controller() {

		};
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
		std::shared_ptr<Db> _db = std::shared_ptr<Db>(new Db());
		DatabaseDiscussionHandling _dbDiscussionHandling;
		DatabaseMessageHandling _dbMessageHandling;
		DatabaseUserFriendHandling _dbUserFriendHandling;
		DatabaseUserHandling _dbUserHandling;
		std::vector<std::function<MessageType (std::shared_ptr<T>, size_t, const char *)>> controllerFunctions;
};

#endif /* !CONTROLLER_HPP_ */
