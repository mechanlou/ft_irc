/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:55:27 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:53:19 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class join : public commands
{
    private:
        bool _check_names(std::string name, std::vector<Channel > *channels);
        void _join_chan(std::string name, Client *cli, std::vector<Channel > *chan,std::vector<pollfd> &fds);
        void _inform_members(std::string name, Client *cli, Channel *chan, std::vector<pollfd> &fds);
    public:
        void execute(std::string buf, Client *cli, std::vector<Channel > *chan, std::vector<pollfd> &fds);
        join();
        ~join();
};

