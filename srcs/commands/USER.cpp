/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:14:14 by wperu             #+#    #+#             */
/*   Updated: 2022/02/16 18:30:28 by rkowalsk         ###   ########lyon.fr   */
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

void user::excute(std::string buf, Client *cli, std::vector<pollfd> &fds)
{
    std::vector<std::string> arg;
    std::string tmp_buf;
    pars_msg(buf,tmp_buf,arg);
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(cli,fds, buf.substr(0, 4));
        return;
    }
    if(arg.size() < 4 || arg[3].empty())
    {
        err_needmoreparams(cli,fds, buf.substr(0, 4));
        return;
    }
    if((cli->get_name().empty() && cli->get_truename().empty() )|| cli->get_register() == false)
    {
        cli->set_name(arg[0]);
        cli->set_truename(arg[3]);
        // std::cout<<cli->get_name()<<" "<<cli->get_truename()<<std::endl;
    }
    else
    {
        err_alreadyregistered(cli,fds);
        return;
    }
}

void user::_register(Client *cli, std::vector<pollfd> &fds)
{
    if(cli->get_name().empty() || cli->get_nickname().empty() || cli->get_truename().empty())
        return;
    if(!cli->get_pass().compare(g_password))
	{
        cli->set_register(true);
		rpl_welcome(cli, fds);
		rpl_yourhost(cli, fds);
		rpl_created(cli, fds);
		rpl_myinfo(cli, fds, "", "");
	}
}
