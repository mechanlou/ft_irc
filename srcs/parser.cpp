/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:13:32 by wperu             #+#    #+#             */
/*   Updated: 2022/02/10 18:06:30 by rkowalsk         ###   ########lyon.fr   */
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
	std::string cmd = get_cmd_from_msg(buf);

	std::cout << "commande : \"" << cmd << "\"" << std::endl;
	// std::cout << "etat : " << cli->get_etat() << " register : " << cli->get_register() << std::endl;
	if(cmd == "PASS")
		_pass.excute(buf, cli,fds);
	else if(cmd == "NICK" && cli->get_etat() == 1)
		_nick.excute(buf,cli, list_chan, list_cli,fds);
	else if(cmd == "USER" && cli->get_etat() == 1)
	{
		_user.excute(buf, cli,fds);
		_user._register(cli);
	}
	else if(cmd == "LIST" && cli->get_register() == true)
		_list.excute(buf,list_chan,cli,fds);	
	else if(cmd == "NAMES" && cli->get_register() == true)
		_names.excute(buf,cli,list_chan,fds);
	else if(cmd == "QUIT" && cli->get_register() == true)
		_quit.excute(buf,cli,list_chan, list_cli, fds);
	else if(cmd == "JOIN" && cli->get_register() == true)
		_join.execute(buf,cli,list_chan,fds);
	else if(cmd == "PART" && cli->get_register() == true)
		_part.execute(buf,cli,list_chan,fds);
	else if(cmd == "TOPIC" && cli->get_register() == true)
		_topic.excute(buf,cli,list_chan,fds);
	else if(cmd == "KICK" && cli->get_register() == true)
		_kick.execute(buf,cli,list_chan,fds);	
	else if(cmd == "PRIVMSG" && cli->get_register() == true)
		_privmsg.execute(buf,cli,list_chan,list_cli,fds);
	else if(cmd == "NOTICE" && cli->get_register() == true)
		_notice.execute(buf,cli,list_chan,list_cli,fds);
	// if(cmd == "MODE")
	// 	_mode.excute();
		
	/*if(cmd == "INVITE")
		_invite.excute();
	*/
}


