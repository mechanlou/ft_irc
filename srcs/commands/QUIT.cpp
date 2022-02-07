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

    for (std::vector<client *>::iterator it = informed.begin(); it != informed.end(); it++)
	{
		client *search = *it;
		if (search->getNick() == dest->getNick())
			return true;
	}
	return false;
}

void _announcement(std::string message, Client *cli, std::vector<Channel *> *chan)
{
	std::vector<client *> informed;
	informed.push_back(cli);

	for (std::vector<channel *>::iterator it = channels->begin(); it != channels->end(); it++)
	{
		channel *c = *it;
		if (c->isMember(cli->getNick()))
		{
			std::vector<client *> cls = c->getMembers();
			for (std::vector<client *>::iterator it2 = cls.begin(); it2 != cls.end(); it2++)
			{
				client *dest = *it2;
				if (!_alreadyInformed(dest, informed))
				{
					send(dest->getSd(), message.c_str(), message.length(), 0);
					informed.push_back(dest);
				}
			}
		//	c->del_cli(cli);
		}
	}
}

void quit::excute(std::string buf, Client *cli, std::vector<Channel *> *chan,std::vector<pollfd> &fds)
{
    std::string bye = buf.substr(5, buf.length() - 5);
	if (bye[0] == ':')
		bye = bye.substr(1, bye.length() - 1);

	buf = ":" + cli->get_nickname() + "!" + cli->get_name() + "@" + cli->get_ip() + " QUIT :Quit: " + bye + "\r\n";
	_informChange(buf, cli, chan);
}