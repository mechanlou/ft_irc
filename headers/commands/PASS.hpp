/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:25:46 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 18:08:55 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class pass: public commands
{
    
    public:
        pass();
        ~pass();
        void excute(std::string buf, Client *cli, std::vector<pollfd> &fds);
};