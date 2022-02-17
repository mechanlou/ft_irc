/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:39 by wperu             #+#    #+#             */
/*   Updated: 2022/02/17 16:53:16 by wperu            ###   ########lyon.fr   */
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
    std::string mdp;
    pars_msg(buf,mdp,arg);
    if(arg.empty())
    {
        err_needmoreparams(cli,fds, buf.substr(0, 4));
        return;
    }
    cli->set_pass(arg[0]);
    cli->set_etat();
}