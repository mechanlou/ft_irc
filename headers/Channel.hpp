#pragma once

#include "ircserver.hpp"

class Client;

class	Channel
{
	public :

	// Channel(void);
	Channel(std::string name);
	Channel(Channel const &src);
	virtual	~Channel(void);
	Channel	&operator=(Channel const &src);


	void 					set_topic(std::string topic);
	void					add_regular_user(Client *user);
	void					add_operator_user(Client *user);
	void					remove_user(Client *user);
	std::string				get_name(void) const;
	std::string				get_topic() const;
	void					set_name(std::string const &new_name);
	bool					is_members(std::string client);
	bool					is_operator(std::string op);
	std::vector<Client *>	get_operators() const;
	std::vector<Client *>	get_all_users() const;

	void			msg_to_channel(const char *msg, std::vector<pollfd> &fds);
	void			msg_to_channel_no_me(const char *msg, std::vector<pollfd> &fds, Client *cli);
	std::string				_name;
	//int size;

	private :

	std::string				_topic;
	std::vector<Client *>	_operators;
	std::vector<Client *>	_all_users;
	
};