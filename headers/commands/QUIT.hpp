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
    public:
        quit();
        ~quit();
        int	excute(std::string buf, Client *cli, std::vector<Channel> *chan, std::vector<Client *> *clients,std::vector<pollfd> &fds);
};