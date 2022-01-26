/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/01/26 17:50:52 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands/commands.hpp"
#include "commands/JOIN.hpp"
#include "commands/PASS.hpp"
#include "commands/USER.hpp"
#include "commands/INVITE.hpp"
#include "commands/PRIVMSG.hpp"
#include "commands/KICK.hpp"
#include "commands/LIST.hpp"
#include "commands/NICK.hpp"
#include "commands/NOTICE.hpp"
#include "commands/KILL.hpp"
#include "commands/PART.hpp"

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
    INVITE		_invite;
	KICK		_kick;
	LIST 		_list;
	NAMES		_names;
	PART		_part;
	KILL		_kill;
	nick		_nick;
	MODE		_mode;
	OPER		_oper;
	PRIVMSG		_privmsg;
	QUIT		_quit;
	WHO			_who;
	NOTICE		_notice;
	TOPIC		_topic;

	std::vector<channel *> channels; 
    
public:
	parser();
	~parser();
    void parse(std::string buf, Client *cli);
    
};

