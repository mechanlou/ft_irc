#include "Channel.hpp"

Channel::Channel(void)
{}

Channel::Channel(std::string name, Client *creator) : name(name)
{
	_all_users.push_back(creator);
	_operators.push_back(creator);
}

Channel::Channel(Channel const &src) : name(src.name),
	_operators(src._operators), _all_users(src._all_users) {}

Channel::~Channel(void) {}

Channel	&Channel::operator=(Channel const &src)
{
	name = src.name;
	_operators = src._operators;
	_all_users = src._all_users;
	return (*this);
}

void	Channel::add_regular_user(Client *user)
{
	_all_users.push_back(user);
}

void	Channel::add_operator_user(Client *user)
{
	_all_users.push_back(user);
	_operators.push_back(user);
}

void	Channel::remove_user(Client *user)
{
	std::vector<Client *>::iterator it;
	std::vector<Client *>::iterator end;

	it = _operators.begin();
	end = _operators.end();
	while (it != end && (*it)->nickname != user->nickname)
		it++;
	if (it != end)
		_operators.erase(it);

	it = _all_users.begin();
	end = _all_users.end();
	while (it != end && (*it)->nickname != user->nickname)
		it++;
	if (it != end)
		_all_users.erase(it);
}

std::vector<Client *>	Channel::get_chan_users(void) const
{
	return (_all_users);
}

std::vector<Client *>	Channel::get_chan_operators(void) const
{
	return (_operators);
}

// int	Channel::msg_to_channel(const char *msg) const
// {
// 	std::vector<Client *>::iterator it;
// 	std::vector<Client *>::iterator end;

// 	it = _all_users.begin();
// 	end = _all_users.end();
// 	while (it != end)
// 	{
// 		if (send_message_fd((*it)->sock_fd, msg) == -1)
// 			return (-1);
// 		it++;
// 	}
// }