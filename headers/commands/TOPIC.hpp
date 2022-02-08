/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:03:46 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 12:33:55 by rkowalsk         ###   ########lyon.fr   */
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
        void excute(std::string buf, Client *cli, std::vector<Channel *> *chan, std::vector<pollfd> &fds);
};