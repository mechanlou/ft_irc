/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:18:48 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:22:37 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NAMES.hpp"

names::names()
{

}

names::~names()
{

}

void names::excute(std::string buf,Client *cli, std::vector<Channel> *chan, std::vector<pollfd> &fds)
{
    std::string msg;
    std::string cli_list;
    Channel *tmp_chan;
    size_t i = 1;
    _getcmd(buf);

    if(_cmd.size() == 2 && _cmd[1] == " ")
        _cmd.pop_back();

    if(_cmd.size() > 1)
    {
        while (i < _cmd.size())
        {
            tmp_chan = _check_chan(_cmd[i], chan);
            if(tmp_chan != NULL)
                rpl_namreply(*cli, fds, *tmp_chan);
            rpl_endofnames(*cli, fds, _cmd[i]);
        }
    }
    
    
}

