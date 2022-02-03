/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:13:32 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 15:10:37 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.hpp"

parser::parser()
{
	
}

parser::~parser()
{
	
}

void parser::parse(std::string buf, Client *cli, std::vector<Client *> *list_cli, std::vector<Channel *> *list_chan)
{
	int space = 0;

	space = buf.find(' ');
	
	std::string com = buf.substr(0,space);
	
	std::cout << "commande =" << com << std::endl;
	
	if(com == "PASS")
		_pass.excute(buf, cli);
		
	if(com == "NICK" && cli->get_etat() == 1)
		_nick.excute(buf,cli, list_chan, list_cli);
		
	if(com == "USER" && cli->get_etat() == 1)
	{
		_user.excute(buf, cli);
		_user._register(cli);
	}	
/*	if(com == "OPER")
		_oper.excute();
		
	if(com == "QUIT")
		_quit.excute();
		
	if(com == "JOIN")
		_join.excute();
		
	if(com == "PART")
		_part.excute();
		
	if(com == "MODE")
		_mode.excute();
		
	if(com == "TOPIC")
		_topic.excute();
		
	if(com == "NAMES")
		_names.excute();
		
	if(com == "LIST")
		_list.excute();
		
	if(com == "INVITE")
		_invite.excute();
		
	if(com == "KICK")
		_kick.excute();
		
	if(com == "PRIVSMG")
		_privmsg.excute();

	if(com == "NOTICE")
		_notice.excute();
	

	
	if(com == "KILL")
		_kill.excute();
	
*/
}


