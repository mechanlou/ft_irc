/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/02/01 15:46:04 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"
#include "JOIN.hpp"
#include "PASS.hpp"
#include "USER.hpp"
#include "PRIVMSG.hpp"
#include "KICK.hpp"
#include "OPER.hpp"
#include "NICK.hpp"
#include "NOTICE.hpp"



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
    void parse(std::string buf, Client *cli, std::vector<Client *> *list_cli, std::vector<Channel *> *list_chan);
    
};

