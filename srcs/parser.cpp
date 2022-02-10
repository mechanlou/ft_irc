/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:13:32 by wperu             #+#    #+#             */
/*   Updated: 2022/02/10 16:05:32 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

parser::parser()
{
	
}

parser::~parser()
{
	
}

void parser::parse(std::string buf, Client *cli, std::vector<Client > *list_cli,
		std::vector<Channel> *list_chan, std::vector<pollfd> &fds)
{
	int space = buf.length();

	space = buf.find(' ');
	
	std::string com = buf.substr(0,space);
	
	std::cout << "commande =" << com << std::endl;
	
	if(com == "PASS")
		_pass.excute(buf, cli,fds);
	else if(com == "NICK" && cli->get_etat() == 1)
		_nick.excute(buf,cli, list_chan, list_cli,fds);
		
	else if(com == "USER" && cli->get_etat() == 1)
	{
		_user.excute(buf, cli,fds);
		_user._register(cli);
	}
	else if(com == "LIST" && cli->get_register() == true)
		_list.excute(buf,list_chan,cli,fds);	
		
	else if(com == "NAMES" && cli->get_register() == true)
		_names.excute(buf,cli,list_chan,fds);
		
	else if(com == "QUIT" && cli->get_register() == true)
		_quit.excute(buf,cli,list_chan, list_cli, fds);
		
	else if(com == "JOIN" && cli->get_register() == true)
		_join.execute(buf,cli,list_chan,fds);
		
	else if(com == "PART" && cli->get_register() == true)
		_part.execute(buf,cli,list_chan,fds);
		
	// if(com == "MODE")
	// 	_mode.excute();
		
	else if(com == "TOPIC" && cli->get_register() == true)
		_topic.excute(buf,cli,list_chan,fds);
				
	/*if(com == "INVITE")
		_invite.excute();
	*/	
	else if(com == "KICK" && cli->get_register() == true)
		_kick.execute(buf,cli,list_chan,fds);
		
	else if(com == "PRIVSMG" && cli->get_register() == true)
		_privmsg.execute(buf,cli,list_chan,list_cli,fds);

	else if(com == "NOTICE" && cli->get_register() == true)
		_notice.execute(buf,cli,list_chan,list_cli,fds);
	
	
	
}


