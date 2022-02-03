/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:49:30 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 18:42:34 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands/JOIN.hpp"
#include "PASS.hpp"
#include "USER.hpp"
#include "PRIVMSG.hpp"
#include "KICK.hpp"
#include "NICK.hpp"
#include "NOTICE.hpp"
#include "TOPIC.hpp"
#include "INVITE.hpp"
#include "MODE.hpp"
#include "LIST.hpp"
#include "NAMES.hpp"
#include "QUIT.hpp"
#include "PART.hpp"

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
    
	public:
	parser();
	~parser();
    void parse(std::string buf, Client *cli, std::vector<Client *> *list_cli,
		std::vector<Channel *> *list_chan, std::vector<pollfd> &fds);
    
};

