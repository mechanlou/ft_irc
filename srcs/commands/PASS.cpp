/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:39 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 16:26:24 by rkowalsk         ###   ########lyon.fr   */
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

void pass::excute(std::string buf, Client *cli)
{
    if(cli->get_register())
    {
        err_alreadyregistered(cli->get_sock_fd());
        return;
    }
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(cli->get_sock_fd(),cli->get_nickname(), buf.substr(0, 4));
        return;
    }
    std::string mdp = buf.substr(5,buf.length() - 5); 
    cli->set_pass(mdp);
    cli->set_etat();
}