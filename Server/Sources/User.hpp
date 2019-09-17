/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** User
*/

#ifndef USER_HPP_
#define USER_HPP_
#include <vector>
class User {
	public:
		User();
		~User();
		std::vector<User> getFriends();
	protected:
	private:
		int _id;
};

#endif /* !USER_HPP_ */
