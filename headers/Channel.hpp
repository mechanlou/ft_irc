#pragma once

#include "ircserver.hpp"

struct Client;

class	Channel
{
	public :

	// Channel(void);
	Channel(std::string name, Client *creator);
	Channel(Channel const &src);
	virtual	~Channel(void);
	Channel	&operator=(Channel const &src);

	void		add_regular_user(Client *user);
	void		add_operator_user(Client *user);
	void		remove_user(Client *user);
	std::string	get_name(void) const;
	void		set_name(std::string const &new_name);

	// int		msg_to_channel(const char *msg) const;
	//std::string				_topic;
	//std::string				_password;
	std::string				_name;
	//int size;

	private :

	
	std::vector<Client *>	_operators;
	std::vector<Client *>	_all_users;
	
	//std::vector<Client *>	_ban;
	//std::vector<Client *>	_speakmodered;
};