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

#include "QUIT.hpp"

quit::quit()
{
}

quit::~quit()
{
}

bool _is_informed(Client *dest, std::vector<Client *> informed)
{

    for (std::vector<Client *>::iterator it = informed.begin(); it != informed.end(); it++)
	{
		Client *search = *it;
		if (search->get_nickname() == dest->get_nickname())
			return true;
	}
	return false;
}

void _announcement(std::string message, Client *cli, std::vector<Channel> *chan)
{
	std::vector<Client *> informed;
	informed.push_back(cli);

	for (std::vector<Channel >::iterator it = chan->begin(); it != chan->end(); it++)
	{
		if (it->is_members(cli->get_nickname()))
		{
			std::vector<Client *> cls = it->get_all_users();
			for (std::vector<Client *>::iterator it2 = cls.begin(); it2 != cls.end(); it2++)
			{
				Client *dest = *it2;
				if (!_is_informed(dest, informed))
				{
					send(dest->get_sock_fd(), message.c_str(), message.length(), 0);
					informed.push_back(dest);
				}
			}
			it->remove_user(cli);
		}
	}
}

void quit::excute(std::string buf, Client *cli, std::vector<Channel> *chan,std::vector<pollfd> &fds)
{
    std::string bye = buf.substr(5, buf.length() - 5);
	if (bye[0] == ':')
		bye = bye.substr(1, bye.length() - 1);

	buf = ":" + cli->get_nickname() + "!" + cli->get_name() + "@" + cli->get_ip() + " QUIT :Quit: " + bye + "\r\n";
	_announcement(buf, cli, chan);
}