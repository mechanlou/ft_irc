/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:35:12 by wperu             #+#    #+#             */
/*   Updated: 2022/02/11 16:22:51 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/commands.hpp"

commands::commands()
{
}

commands::~commands()
{
}

Channel* commands::_check_chan(std::string name, std::vector<Channel > *chan) const
{
    std::vector<Channel >::iterator it = chan->begin();
    for(;it != chan->end(); it++)
    {
        if(name == (*it).get_name())
            return (&(*it));
    }
    return (NULL);
}

bool commands::_check_client(Client *user, Channel *chan)
{
    std::vector<Client *> members = chan->get_all_users();
    std::vector<Client *>::iterator it = members.begin();
    Client *c;
    
   for(;it != members.end() ; it++)
   {
       c = *it;
       if(user->get_sock_fd() == c->get_sock_fd())
        return true;
   }
   return false;
}


void commands::_getcmd(std::string buf)
{
    char space = ' ';
    std::vector<std::string> cmd_tmp;
    std::string line;
    std::stringstream ss(buf);
    while (std::getline(ss,line,space))
    {
        while(line.back() == '\n' || line.back() == '\r')
            line.pop_back();
        cmd_tmp.push_back(line);
    }
    while(cmd_tmp.back() == "\n" || cmd_tmp.back() == "\r" || cmd_tmp.back().size() == 0)
        cmd_tmp.pop_back();
    if(cmd_tmp.size() > 2 && cmd_tmp[2][0] == ':')
        cmd_tmp[2] = &cmd_tmp[2][1];
    _cmd.clear();
    _cmd = cmd_tmp;
    
    for(std::vector<std::string>::iterator it = _cmd.begin(); it != _cmd.end();it++)
    {
        std::cout << "cmd =  "<< *it << std::endl;
    }    
}