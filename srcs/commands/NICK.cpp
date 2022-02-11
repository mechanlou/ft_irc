/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:43 by wperu             #+#    #+#             */
/*   Updated: 2022/02/11 15:49:36 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/NICK.hpp"

nick::nick()
{
    
}

nick::~nick()
{
    
}

bool nick:: _checknick(std::string user, std::vector<Client > *clients)
{
    for (std::vector<Client >::iterator it = clients->begin(); it != clients->end(); it++)
	{
		if (it->get_nickname() == user)
			return false;
	}
	return true;
}

bool nick::_validnick(std::string nick)
{
    size_t i = 0;
	
	std::cout<<"|"+nick+"|"<<std::endl;
	while (i < nick.length())
	{
		if (nick[i] <= 32 || nick[i] > 126 || nick[i] == ':' || nick[i] == '#' || nick[i] == '!' || nick[i] == '@')
			return false;
		i++;
	}
    return true;
}

bool nick::_is_informed(Client *dest, std::vector<Client > informed)
{
	for(std::vector<Client >::iterator it = informed.begin(); it != informed.end(); it++)
	{
		if(it->get_nickname() == dest->get_nickname())
			return true;
	}
	return false;
}


void nick:: _announcement_new_nick(std::string message, Client *cli,std::vector<Channel > *chan)
{
    std::vector<Client > informe;
	
	for(std::vector<Channel >::iterator it = chan->begin(); it != chan->end(); it++)
	{
		if(it->is_members(cli->get_nickname()))
		{
			std::vector<Client *> clis = it->get_all_users();
			for(std::vector<Client *>::iterator its = clis.begin(); its != clis.end();its++)
			{
				Client *dest = *its;
				if(!_is_informed(dest,informe))
				send(dest->get_sock_fd(),message.c_str(),message.length(),0);
				informe.push_back(*dest);
			}
		}
	}
}

void nick::excute(std::string buf, Client *cli, std::vector<Channel > *chan, std::vector<Client> *Clients, std::vector<pollfd> &fds)
{
    std::string cmd;
	std::vector<std::string> args;

	pars_msg(buf, cmd, args);
    if(args.empty())
    {
        err_nonicknamegiven(*cli,fds);
		return ;
    }
    if(args[0] == cli->get_nickname())
        return;
    if (!_validnick(args[0]))
	{
		err_erroneusnickname(*cli,fds);
		return ;
	}
	if (!_checknick(args[0], Clients))
	{
		err_nicknameinuse(*cli,fds);
		return ;
	}
	puts("oknick");
    cmd = ":" + cli->get_nickname() + " NICK " + args[0] + END_OF_MSG;
	cli->set_nickname(args[0]);
    
    _announcement_new_nick(cmd, cli, chan);
}      
