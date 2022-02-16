/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:39 by wperu             #+#    #+#             */
/*   Updated: 2022/02/16 17:10:28 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/PASS.hpp"

pass::pass()
{
    
}

pass::~pass()
{
    
}

void pass::excute(std::string buf, Client *cli, std::vector<pollfd> &fds)
{
    std::vector<std::string> arg;
    if(cli->get_register())
    {
        err_alreadyregistered(cli,fds);
        return;
    }
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(cli,fds, buf.substr(0, 4));
        return;
    }
    std::string mdp;
    pars_msg(buf,mdp,arg);
    std::cout<<arg[0]<<std::endl;
    cli->set_pass(arg[0]);
    cli->set_etat();
}