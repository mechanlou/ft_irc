/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:08:24 by wperu             #+#    #+#             */
/*   Updated: 2022/02/16 17:06:56 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/LIST.hpp"

list::list()
{
	
}

list::~list()
{
	
}

void list::excute(std::string msg, std::vector<Channel> *all_channels,
	Client *src,std::vector<pollfd> &fds)
{
	std::vector<Channel>::iterator	it;
	std::vector<Channel>::iterator	it_end;
	Channel							*tmp_chan;
	std::string 					cmd;
	std::vector<std::string>		args;
	std::string						chan_name;
	std::istringstream				names_list;
	std::ostringstream				conv;

	pars_msg(msg, cmd, args);
	if (args.size() > 0)
	{
		names_list.str(args[0]);
		while (std::getline(names_list, chan_name, ','))
		{
			tmp_chan = _check_chan(chan_name, all_channels);
			if(tmp_chan != NULL)
			{
				conv.str("");
				conv << tmp_chan->get_all_users().size();
				rpl_list(src, fds, tmp_chan->get_name(), conv.str(), tmp_chan->get_topic());
			}
		}
		rpl_listend(src, fds);
	}
	else
	{
		it = all_channels->begin();
		it_end = all_channels->end();
		while (it != it_end)
		{
			conv.str("");
			conv << it->get_all_users().size();
			rpl_list(src, fds, it->get_name(), conv.str(), it->get_topic());
			it++;
		}
		rpl_listend(src, fds);
	} 
}
