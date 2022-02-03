/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 16:52:29 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands/JOIN.hpp"
#include "commands/PASS.hpp"
#include "commands/USER.hpp"
#include "commands/PRIVMSG.hpp"
#include "commands/KICK.hpp"
#include "commands/OPER.hpp"
#include "commands/NICK.hpp"
#include "commands/NOTICE.hpp"



#include "Channel.hpp"
#include "ircserver.hpp"

class client;
class channel;

class parser
{
private:
    
    pass		_pass;
    user		_user;
	nick		_nick;
	join		_join;
/*	kick		_kick;
	oper		_oper;
	privmsg		_privmsg;
	quit	_quit;
	notice		_notice;*/

	//std::vector<channel *> channels; 
    
public:
	parser();
	~parser();
    void parse(std::string buf, Client *cli, std::vector<Client *> *list_cli,
		std::vector<Channel *> *list_chan, std::vector<pollfd> &fds);
    
};

