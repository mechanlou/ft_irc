/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:39 by wperu             #+#    #+#             */
/*   Updated: 2022/01/31 18:20:24 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "PASS.hpp"

pass::pass()
{
    
}

pass::~pass()
{
    
}

int pass::excute(std::string buf, Client *cli)
{
    if(buf.find(' ') == buf.npos)
    {
        err_needmoreparams(cli->get_sock_fd(),cli->get_nickname(), buf.substr(0, 4));
    }
    std::string mdp = buf.substr(5,buf.lenght() - 5); 
    if(mdp == PASSWORD)
    {
        cli->set_etat();
    }
}