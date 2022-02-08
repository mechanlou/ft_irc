/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:03:46 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:30:31 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include "commands.hpp"

class topic : public commands
{
    private :
        void get_cmd(std::string buf);

    public:
        topic();
        ~topic();
        void excute(std::string buf, Client *cli, std::vector<Channel > *chan, std::vector<pollfd> &fds);
};