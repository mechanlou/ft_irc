/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:16:03 by wperu             #+#    #+#             */
/*   Updated: 2022/02/01 14:29:04 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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