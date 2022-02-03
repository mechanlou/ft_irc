/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:08:24 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 16:03:27 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "LIST.hpp"

list::list()
{
    
}

list::~list()
{
    
}

void list::excute(std::string cmd, std::vector<Channel *> *chan, Client *cli)
{
    _getcmd(cmd);
    std::string list_chan;
    Channel *cur_chan;
    size_t i  = 0;
        
    if(_cmd.size() > 1)
    {
        rpl_liststart(cli->get_sock_fd());
        while(i < _cmd.size())
        {
                cur_chan = _check_chan(_cmd[i],chan);
                list_chan.append(cli->get_nickname() + " " + cur_chan->get_name() + std::to_string(cur_chan->get_all_users().size()));
                list_chan.append(":" + cur_chan->get_topic());
                rpl_list(*cli,list_chan);
                list_chan.clear();
                i++;
        }
           
    }
    
    if(_cmd.size() == 1)
    {    
        rpl_liststart(*cli,);
        for(std::vector<Channel *>:: iterator it = chan->begin(); it != chan->end(); it++)
        {
            list_chan.append(cli->get_nickname() + " " + (*it)->get_name() + std::to_string((*it)->get_all_users().size()));
            list_chan.append(":" + (*it)->get_topic());
            rpl_list(cli->get_sock_fd(),list_chan);
        }
        list_chan.clear();
    }
    rpl_listend(cli->get_sock_fd(),cli->get_nickname());   
}