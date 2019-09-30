/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** User
*/

#ifndef USER_HPP_
#define USER_HPP_
#include <vector>
#include "NetworkClient.hpp"
class User : public Babel::Network::NetworkClient {
	public:
            User(int fd, struct sockaddr_in *sockaddrIn);
            ~User();
	    bool isLogged() const {return _logged;};
            void onMessage(std::vector<uint8_t> &buff);
	    void login(int id);
	    std::vector<User> getFriends();
	    int getID() const;
	protected:
	private:
		bool _logged = false;
		int _id;
};

#endif /* !USER_HPP_ */
