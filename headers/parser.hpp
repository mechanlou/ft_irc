/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/01/31 17:32:22 by wperu            ###   ########lyon.fr   */
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
    JOIN		_join;
    pass		_pass;
    user		_user;
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

