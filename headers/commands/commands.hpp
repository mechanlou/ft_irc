/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:11:39 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:17:53 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Channel.hpp"
#include "ircserver.hpp"
#include "Client.hpp"

class commands
{           
    protected:
        std::vector<std::string> _cmd;
        
        Channel* _check_chan(std::string name, std::vector<Channel> *chan) const;
        bool     _check_client(Client *user, Channel *chan);
        void     _getcmd(std::string buf);
    public:
        
        commands();
        virtual ~commands();
};