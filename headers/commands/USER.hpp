/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:16:03 by wperu             #+#    #+#             */
/*   Updated: 2022/02/16 18:31:30 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class user: public commands
{
    private:
        int _check_arg(std::string buf);
    public:
        user();
        ~user();
        void excute(std::string buf, Client *cli, std::vector<pollfd> &fds);
        void _register(Client *cli, std::vector<pollfd> &fds);
};