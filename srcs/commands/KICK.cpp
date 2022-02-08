/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:36 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 15:45:54 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "KICK.hpp"

kick::kick()
{
}

kick::~kick()
{
}


bool kick::_check_Client_nick(std::string cli, Channel *chan)
{
    std::vector<Client *> members = chan->get_all_users();
    for (std::vector<Client *>::iterator it = members.begin(); it != members.end(); it++)
	{
		Client *c = *it;
		if (c->get_nickname() == cli)
			return true;
	}
	return false;
}

void	kick::_inform_members(std::string msg, Channel *chan)
{
	Client *c;
	std::vector<Client*> members = chan->get_all_users();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		//send(c->getSd(), msg.c_str(), msg.length(), 0); change fnct send;
	}
}

Client*	kick::_get_Client(std::string name, Channel *chan)
{
	Client *c;
	std::vector<Client*> members = chan->get_all_users();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->get_nickname() == name)
			return c;
	}
	return NULL;
}

void	kick::execute(std::string buf, Client *cli, std::vector<Channel *> *channels,std::vector<pollfd> &fds)
{
	_getcmd(buf);
	std::string msg;
	Channel *chan = _check_chan(_cmd[1], channels);

	if (chan == NULL)
	{
		err_nosuchchannel(*cli,fds,_cmd[1]);;
		return ;
	}
	if (_cmd[2].empty())
	{
           err_needmoreparams(*cli,fds,_cmd[0]);
		return ;
	}
	if (!_check_client(cli, chan))
	{
           err_notochannel(*cli,fds,_cmd[1]);
		return ;
	}
	if (!chan->is_operator(cli))
	{
		err_chanoprivsneeded(*cli,fds,_cmd[1]);
		return ;
	}
	if (!_check_Client_nick(_cmd[2], chan))
	{
           err_usernotinchannel(*cli,fds,_cmd[2],_cmd[1]);
		return ;
	}
	std::string reason;
	if (_cmd.size() > 3)
	{
		size_t i = 3;
		while (i < _cmd.size())
		{
			reason += _cmd[i] + " ";
			i++;
		}
		reason.pop_back();
	}
	std::cout << "reason : " << reason << std::endl;
	if (reason.size() >= 1 && reason[0] != ':')
		reason = ':' + reason;
	msg = ":" + cli->get_nickname() + " KICK " + _cmd[1] + " " + _cmd[2] + " " + reason + "\r\n";
	_inform_members(msg, chan);
	chan->del_cli(_get_Client(_cmd[2], chan));
}