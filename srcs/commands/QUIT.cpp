/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:18 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 12:07:18 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/QUIT.hpp"

quit::quit()
{
}

quit::~quit()
{
}

bool quit::_is_informed(Client *dest, std::vector<Client *> informed)
{

    for (std::vector<Client *>::iterator it = informed.begin(); it != informed.end(); it++)
	{
		Client *search = *it;
		if (search->get_nickname() == dest->get_nickname())
			return true;
	}
	return false;
}

void quit::_announcement(std::string message, Client *cli, std::vector<Channel> *chan,std::vector<pollfd> &fds)
{
	std::vector<Client *> informed;
	informed.push_back(cli);

	for (std::vector<Channel >::iterator it = chan->begin(); it != chan->end(); it++)
	{
		if (it->is_members(cli->get_nickname()))
		{
			std::vector<Client *> cls = it->get_all_users();
			it->remove_user(cli);
			it->msg_to_channel(message.c_str(), fds);
		}
	}
}

int	quit::excute(std::string buf, Client *cli, std::vector<Channel> *chan, std::vector<Client> *clients,std::vector<pollfd> &fds)
{
    std::string bye = buf.substr(5, buf.length() - 5);
	if (bye[0] == ':')
		bye = bye.substr(1, bye.length() - 1);

	buf = ":" + cli->get_nickname() + "!" + cli->get_name() + "@" + cli->get_ip() + " QUIT :Quit: " + bye + END_OF_MSG;
	_announcement(buf, cli, chan, fds);
	return (close_connection(cli->get_sock_fd(), fds, *clients, *chan));
}