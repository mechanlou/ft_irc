/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/01/27 15:39:32 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands/commands.hpp"
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
    JOIN		_join;
    PASS		_pass;
    USER		_user;
	KICK		_kick;
	nick		_nick;
	OPER		_oper;
	PRIVMSG		_privmsg;
	QUIT		_quit;
	NOTICE		_notice;


	std::vector<channel *> channels; 
    
public:
	parser();
	~parser();
    void parse(std::string buf, Client *cli);
    
};

