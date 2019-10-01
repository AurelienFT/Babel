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
	    /**
	     * Constructor : Initialize a client instance
	     * @param fd socket file descriptor
	     * @param sockaddrIn socket structure to fill
	     */
            User(int fd, struct sockaddr_in *sockaddrIn);
	    /**
	     * Destructor
	     */
            ~User();
	    /**
	     * Check if the user is logged
	     * @return true if logged, false if not
	     */
	    bool isLogged() const {return _logged;};
	    /**
	     * Login the user
	     * @param id ID of the user get in the database
	     */
	    void login(int id);
	    /** Get all the friends of a user
	     * @return Vector with all friends
	    */
	    std::vector<User> getFriends();
	    /**
	     * Get ID of the user
	     * @return ID of the user
	     */
	    int getID() const;
	protected:
	private:
		bool _logged = false;
		int _id;
};

#endif /* !USER_HPP_ */
