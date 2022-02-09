/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:14:14 by wperu             #+#    #+#             */
/*   Updated: 2022/02/09 12:20:19 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/USER.hpp"

user::user()
{

}

user::~user()
{

}

int user::_check_arg(std::string buf)
{
        int i = 0;
        while (buf.find(' ') != buf.npos)
        {
            i++;
            buf = buf.substr(buf.find(' ') + 1,buf.length() - buf.find(' ') + 1);
        }
        return (i);
}

void user::excute(std::string buf, Client *cli,std::vector<pollfd> &fds)
{
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(*cli,fds, buf.substr(0, 4));
        return;
    }
    buf = buf.substr(5, buf.length() - 5);
    std::string user = buf.substr(0,buf.find(' '));
    std::string realname;
    
    if(buf.find('*') != buf.npos)
    {
        realname = buf.substr(buf.find('*') + 2, buf.length() - buf.find('*') + 2);
        if(realname[0] == ':')
            realname = realname.substr(1,realname.length() - 1);
        if(realname.find('\r') != buf.npos)
            realname = realname.substr(0, realname.length() - 2);
        else
            realname.pop_back();
    }
    if(realname.empty() || _check_arg(buf) < 3)
    {
        err_needmoreparams(*cli,fds, buf.substr(0, 4));
        return;
    }
    
    if(cli->get_name().empty() && cli->get_truename().empty())
    {
        cli->set_name(user);
        cli->set_name(realname);
    }
    else
    {
        err_alreadyregistered(*cli,fds);
        return;
    }
}

void user::_register(Client *cli)
{
    
    if(cli->get_name().empty() || cli->get_nickname().empty() || cli->get_truename().empty())
        return;
    if(cli->get_pass() == g_password)
    {
        cli->set_register(true);
    }
}
