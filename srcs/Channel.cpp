#include "ircserver.hpp"

Channel::Channel(std::string name, Client *creator) : _name(name)
{
	_all_users.push_back(creator);
	_operators.push_back(creator);
}

Channel::Channel(Channel const &src) : _name(src._name),
	_operators(src._operators), _all_users(src._all_users) {}

Channel::~Channel(void) {}

Channel	&Channel::operator=(Channel const &src)
{
	_name = src._name;
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
	while (it != end && (*it)->get_nickname() != user->get_nickname())
		it++;
	if (it != end)
		_operators.erase(it);

	it = _all_users.begin();
	end = _all_users.end();
	while (it != end && (*it)->get_nickname() != user->get_nickname())
		it++;
	if (it != end)
		_all_users.erase(it);
}

std::vector<Client *>	Channel::get_all_users() const
{
	return (_all_users);
}

std::vector<Client *>	Channel::get_operators() const
{
	return (_operators);
}

std::string Channel::get_topic() const
{
	return(_topic);
}

void Channel::set_topic(std::string topic)
{
	_topic = topic;
}

// bool Channel::is_members(std::string client)
// {
	
// }

void	Channel::msg_to_channel(const char *msg, std::vector<pollfd> &fds)
{
	std::vector<Client *>::iterator it;
	std::vector<Client *>::iterator end;

	it = _all_users.begin();
	end = _all_users.end();
	while (it != end)
	{
		send_msg_client(**it, fds, msg);
		it++;
	}
}