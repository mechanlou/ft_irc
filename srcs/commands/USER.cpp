/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:14:14 by wperu             #+#    #+#             */
/*   Updated: 2022/02/11 15:29:16 by wperu            ###   ########lyon.fr   */
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
    std::string tmp_buf;
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(*cli,fds, buf.substr(0, 4));
        return;
    }
    tmp_buf = buf.substr(5, buf.length() - 5);
    std::string user = tmp_buf.substr(0,buf.find(' '));
    std::string realname;
    
    if(buf.find('*') != tmp_buf.npos)
    {
        realname = tmp_buf.substr(tmp_buf.find('*') + 2, tmp_buf.length() - tmp_buf.find('*') + 2);
        if(realname[0] == ':')
            realname = realname.substr(1,realname.length() - 1);
        if(realname.find('\r') != tmp_buf.npos)
            realname = realname.substr(0, realname.length() - 2);
        else
            realname.pop_back();
    }
    if(realname.empty() || _check_arg(tmp_buf) < 3)
    {
        err_needmoreparams(*cli,fds, buf.substr(0, 4));
        return;
    }
    std::cout<<realname<<" "<<user<<std::endl;
    if((cli->get_name().empty() && cli->get_truename().empty() )|| cli->get_register() == false)
    {
        cli->set_name(user);
        cli->set_truename(realname);
    }
    else
    {
        err_alreadyregistered(*cli,fds);
        return;
    }
}

void user::_register(Client *cli)
{
    std::cout<<"|"+cli->get_pass()+"|"<<" "<<"|"<< g_password <<"|"<<std::endl;
    if(cli->get_name().empty() || cli->get_nickname().empty() || cli->get_truename().empty())
        return;
    if(!cli->get_pass().compare(g_password))
        cli->set_register(true);
}
