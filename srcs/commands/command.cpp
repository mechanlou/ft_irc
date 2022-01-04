/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:35:12 by wperu             #+#    #+#             */
/*   Updated: 2022/01/04 17:18:49 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

commands::commands()
{
}

commands::~commands()
{
}

Channel* commands::_check_chan(std::string name, std::vector<Channel *> *chan) const
{
    std::vector<Channel>::iterator it = chan->begin();
    Channel *c;
    for(;it != chan->end(); it++)
    {
        c = *it;
        if(name == c->get_name())
            return chan;
    }
    return (NULL);
}

bool commands::_check_client(client *user, Channel *chan)
{
    std::vector<Client*> members = chan->getMember();
    std::vector<Channel>::iterator it = chan->begin();
    client *c;
    
   for(;it != chan->end() ; it++)
   {
       c = *it;
       if(user->get_sock_fd() == c->get_sock_fd)
        return true;
   }    
   return false;
}
