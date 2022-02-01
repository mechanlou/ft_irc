/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:11:39 by wperu             #+#    #+#             */
/*   Updated: 2022/01/26 17:23:42 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "ircserver.hpp"
#include "Client.hpp"

class commands
{
    protected:
        Channel* _check_chan(std::string name, std::vector<Channel *> *chan) const;
        bool     _check_client(Client *user, Channel *chan);
    public:
        commands();
        virtual ~commands();
};