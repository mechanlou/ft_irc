/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:43:39 by wperu             #+#    #+#             */
/*   Updated: 2022/01/21 10:42:22 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/commands/commands.hpp"

int checkpass(Client *cli ,std::string pass)
{
    if(pass.empty())
        return(ERR_NEEDMOREPARAMS); 
    if(cli->etat != 0)
        return(ERR_ALREADYREGISTRED);
    if(pass == PASSWORD)
        cli->etat++;
    else
     send_message_fd(cli->sock_fd,"bad password");
    return(0);
}