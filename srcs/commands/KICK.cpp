/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:36 by wperu             #+#    #+#             */
/*   Updated: 2022/02/17 17:14:23 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/KICK.hpp"

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

void	kick::execute(std::string buf, Client *cli, std::vector<Channel > *channels,std::vector<pollfd> &fds)
{
	std::vector<std::string> cmd;
	std::string arg;
	pars_msg(buf,arg,cmd);
	std::string msg;

	if (cmd.empty())
	{
           err_needmoreparams(cli,fds,arg);
		return ;
	}
	Channel *chan = _check_chan(cmd[0], channels);
	if (chan == NULL)
	{
		err_nosuchchannel(cli,fds,cmd[0]);;
		return ;
	}
	if (!_check_client(cli, chan))
	{
           err_notochannel(cli,fds,cmd[0]);
		return ;
	}
	if (!chan->is_operator(cli->get_nickname()))
	{
		err_chanoprivsneeded(cli,fds,cmd[0]);
		return ;
	}
	if (!_check_Client_nick(cmd[1], chan))
	{
           err_usernotinchannel(cli,fds,cmd[1],cmd[0]);
		return ;
	}
	std::string reason;
	if (cmd.size() > 2)
	{
		size_t i = 2;
		while (i < cmd.size())
		{
			reason += cmd[i] + " ";
			i++;
		}
		reason.pop_back();
	}
	if (reason.size() >= 1 && reason[0] != ':')
		reason = ':' + reason;
	msg = ":" + cli->get_nickname() + " KICK " + cmd[0] + " " + cmd[1] + " " + reason + END_OF_MSG;
	chan->msg_to_channel(msg.c_str(), fds);
	chan->remove_user(_get_Client(cmd[1], chan));
}