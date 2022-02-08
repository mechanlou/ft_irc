/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 16:08:15 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands/JOIN.hpp"
#include "commands/PASS.hpp"
#include "commands/USER.hpp"
#include "commands/PRIVMSG.hpp"
#include "commands/KICK.hpp"
#include "commands/NICK.hpp"
#include "commands/NOTICE.hpp"
#include "commands/TOPIC.hpp"
// #include "commands/INVITE.hpp"
//#include "commands/MODE.hpp"
#include "commands/LIST.hpp"
#include "commands/NAMES.hpp"
#include "commands/QUIT.hpp"
#include "commands/PART.hpp"

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
		list		_list;
		names		_names;
		privmsg		_privmsg;
		part		_part;
		quit		_quit;
		notice		_notice;
		topic		_topic;
		kick		_kick;
		
	public:
	parser();
	~parser();
    void parse(std::string buf, Client *cli, std::vector<Client > *list_cli,
		std::vector<Channel > *list_chan, std::vector<pollfd> &fds);
    
};

