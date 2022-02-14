/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:18:48 by wperu             #+#    #+#             */
/*   Updated: 2022/02/14 14:40:15 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/NAMES.hpp"

names::names()
{

}

names::~names()
{

}

void names::excute(std::string buf, Client *src,
	std::vector<Channel> *all_channels, std::vector<Client> *all_clients,
	std::vector<pollfd> &fds)
{
	std::vector<Channel>::iterator	it;
	std::vector<Channel>::iterator	it_end;
	Channel							*tmp_chan;
	std::string 					cmd;
	std::vector<std::string>		args;
	std::string						chan_name;
	std::istringstream				names_list;

	pars_msg(buf, cmd, args);
	if (args.size() > 0)
	{
		names_list.str(args[0]);
		while (std::getline(names_list, chan_name, ','))
		{
			tmp_chan = _check_chan(chan_name, all_channels);
			if(tmp_chan != NULL)
				rpl_namreply(*src, fds, *tmp_chan);
			rpl_endofnames(*src, fds, chan_name);
		}
	}
	else
	{
		it = all_channels->begin();
		it_end = all_channels->end();
		while (it != it_end)
		{
			rpl_namreply(*src, fds, *it);
			it++;
		}
		rpl_namreply_other_clients(*src, fds, *all_channels, *all_clients);
		rpl_endofnames(*src, fds, "*");
	}
}
