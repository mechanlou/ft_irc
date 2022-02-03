/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:16:03 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 16:27:13 by rkowalsk         ###   ########lyon.fr   */
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
        void excute(std::string buf, Client *cli);
        void _register(Client *cli);
};