#include "ircserver.hpp"
#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{

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

bool Channel::is_members(std::string client)
{
	for(std::vector<Client *>::iterator it = _all_users.begin(); it != _all_users.end(); it++)
	{
		if((*it)->get_nickname() == client)
			return true;
	}
	return false;
}

bool Channel::is_operator(std::string op)
{
	for(std::vector<Client *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if((*it)->get_nickname() == op)
			return true;
	}
	return false;
}

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

void	Channel::msg_to_channel_no_me(const char *msg, std::vector<pollfd> &fds, Client *cli)
{
	std::vector<Client *>::iterator it;
	std::vector<Client *>::iterator end;

	it = _all_users.begin();
	end = _all_users.end();
	while (it != end)
	{
		if(cli->get_nickname() != (*it)->get_nickname())
			send_msg_client(**it, fds, msg);
		it++;
	}
}

std::string	Channel::get_name(void) const
{
	return (_name);
}
