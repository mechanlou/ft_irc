/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:56:20 by wperu             #+#    #+#             */
/*   Updated: 2022/02/11 16:29:07 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/JOIN.hpp"

join::join()
{   
}

join::~join()
{

}


void join::execute(std::string buf, Client *cli, std::vector<Channel> *chan, std::vector<pollfd> &fds)
{
    _getcmd(buf);
	
    if (_cmd.size() < 2)
    {
        err_needmoreparams(*cli, fds, _cmd[0]);
        return;
    }
    if (_cmd[1][0] && _cmd[1][0] != '#')
		_cmd[1] = '#' + _cmd[1];
	if (!_check_names(_cmd[1], chan))
	{
		Channel nchan(_cmd[1],cli);
		chan->push_back(nchan);
	}
	_join_chan(_cmd[1], cli, chan,fds);
}

bool join::_check_names(std::string name, std::vector<Channel > *channels)
{
    for (std::vector<Channel >::iterator it = channels->begin(); it != channels->end(); it++)
	{
		if (it->get_name() == name)
			return true;
	}
	return false;
}

void	join::_join_chan(std::string name, Client *cli, std::vector<Channel> *channels, std::vector<pollfd> &fds)
{
	bool new_cli = false;
	std::string tmp;
    Channel *chan = _check_chan(name, channels);
	
    if (chan->is_members(cli->get_nickname()))
	{
		err_useronchannel(*cli,fds,name);
		return;
    }
    else
    {
        chan->add_regular_user(cli);
	    if (chan->get_all_users().size() == 1)
			chan->add_operator_user(cli);
		new_cli = true;
    }

    _inform_members(name, cli, chan, fds);

    if(new_cli)
    {
        rpl_topic(*cli, fds, name, chan->get_topic());
    }
}

void	join::_inform_members(std::string name, Client *cli, Channel *chan, std::vector<pollfd> &fds)
{
	std::string msg = ":" + cli->get_nickname() + "!" + cli->get_name() + "@" + cli->get_ip() + " JOIN " + name + END_OF_MSG;
	std::vector<Client*> members = chan->get_all_users();
	chan->msg_to_channel(msg.c_str(), fds);
}