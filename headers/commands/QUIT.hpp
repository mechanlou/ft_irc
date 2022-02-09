/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:49 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 12:07:49 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class quit : public commands
{
    private:
        bool _is_informed(Client *dest, std::vector<Client *> informed);
        void _announcement(std::string message, Client *cli,std::vector<Channel > *chan, std::vector<pollfd> &fds);
    
    public:
        quit();
        ~quit();
        int	excute(std::string buf, Client *cli, std::vector<Channel> *chan, std::vector<Client> *clients,std::vector<pollfd> &fds);
};