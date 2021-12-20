#pragma once

#include "ircserver.hpp"

struct Client;

class	Channel
{
	public :

	std::string	name;

	Channel(void);
	Channel(std::string name, Client *creator);
	Channel(Channel const &src);
	virtual	~Channel(void);
	Channel	&operator=(Channel const &src);

	void		add_regular_user(Client *user);
	void		add_operator_user(Client *user);
	void		remove_user(Client *user);

	std::vector<Client *>	get_chan_users(void) const;
	std::vector<Client *>	get_chan_operators(void) const;

	// int		msg_to_channel(const char *msg) const;

	private :

	std::vector<Client *>	_operators;
	std::vector<Client *>	_all_users;
};