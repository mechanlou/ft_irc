/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:03:46 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 11:20:26 by wperu            ###   ########lyon.fr   */
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
        void excute(std::string buf, client *cli, std::vecor<Channel *> *chan, std::vector<pollfd> &fds);
}