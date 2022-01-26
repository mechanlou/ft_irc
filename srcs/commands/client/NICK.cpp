/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:43 by wperu             #+#    #+#             */
/*   Updated: 2022/01/26 15:31:16 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/commands/NICK.hpp"

nick::nick()
{
    
}

nick::~nick()
{
    
}

bool nick:: _checknick(std::string user, std::vector<Client *> *clients)
{
    for (std::vector<Client *>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		Client *c = *it;
		if (c->get_nick() == user)
			return false;
	}
	return true;
}

bool nick::_validnick(std::string nick)
{
    size_t i = 0;
	while (i < nick.length())
	{
		if (nick[i] <= 32 || nick[i] > 126 || nick[i] == ':' || nick[i] == '#' || nick[i] == '!' || nick[i] == '@')
			return false;
		i++;
	}
    return true;
}

void nick:: _announcement_new_nick(std::string message, Client *cli,std::vector<Channel *> *chan)
{
    std::vector<Client *> informe;
	
	for(std::vector<Channel *>::iterator it = chan->begin(); it != chan->end(); it++)
	{
		Channel *c = *it;
		if(c->is_members(cli->get_nick))
	}
}

void nick::excute(std::string buf, Client *cli, std::vector<Channel *> *chan, std::vector<Client *> *Clients)
{
    std::string message;
    if(buf.find(' ') == buf.npos)
    {
        message = ":server " + std::string(ERR_NONICKNAMEGIVEN) + ":No nickname given\r\n";
        send(cli->get_sock_fd(), message.c_str(), message.length(), 0);
		return ;
    }

    int begin = buf.find(' ') + 1;
    int len = buf.length() - begin + 1;
    if(buf.find('/r') != buf.npos)
        len = buf.find('/r') - begin;
    std::string nick = buf.substr(begin,len);
    if(nick[0] == ':')
        nick = nick.substr(1, nick.length() - 1);
    if(nick == cli->get_nickname())
        return;
    if (!_validnick(nick))
	{
		message = ":server " + std::string(ERR_ERRONEUSNICKNAME) + " nick: Erroneus nickname\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}
	if (!_checknick(nick, Clients))
	{
		message = ":server " + std::string(ERR_NICKNAMEINUSE) + " nick: Nickname is already in use\r\n";
		send(cli->getSd(), message.c_str(), message.length(), 0);
		return ;
	}

    message = ":" + cli->getNick() + " NICK " + nick +"\r\n";
	cli->setNick(nick);
    
    _announcement_new_nick(message, cli, chan);
}      
