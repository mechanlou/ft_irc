/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:55:27 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 02:11:22 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class join : public commands
{
    private:
        bool _check_names(std::string name, std::vector<Channel *> *channels);
        void _join_chan(std::string name, Client *cli, std::vector<Channel *> *chan);
        void _inform_members(std::string name, Client *cli, Channel *chan);
    public:
        void execute(std::string buf, Client *client, std::vector<Channel *> *chan, std::vector<pollfd> &fds);
        join(){};
        ~join(){};
};

