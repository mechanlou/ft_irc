/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:10:27 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:22:47 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class names : public commands
{
    public:
        names();
        ~names();
        void excute(std::string buf, Client *cli, std::vector<Channel > *chan, std::vector<pollfd> &fds);
        void displayname(Channel *chan, Client *cli);
};