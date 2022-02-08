/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:05:36 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:25:32 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class list : public commands
{
    public:
    list();
    ~list();
    void excute(std::string cmd, std::vector<Channel> *chan, Client *cli, std::vector<pollfd> &fds);
};

