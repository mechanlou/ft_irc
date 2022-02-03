/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:39 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 18:24:46 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ircserver.hpp"
#include "PASS.hpp"

pass::pass()
{
    
}

pass::~pass()
{
    
}

void pass::excute(std::string buf, Client *cli, std::vector<pollfd> &fds)
{
    if(cli->get_register())
    {
        err_alreadyregistered(*cli,fds);
        return;
    }
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(*cli,fds, buf.substr(0, 4));
        return;
    }
    std::string mdp = buf.substr(5,buf.length() - 5); 
    cli->set_pass(mdp);
    cli->set_etat();
}