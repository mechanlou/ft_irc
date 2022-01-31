/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:25:46 by wperu             #+#    #+#             */
/*   Updated: 2022/01/31 16:12:32 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

class pass: public commands
{
    private:
    
    public:
        pass();
        ~pass();
        void excute(std::string buf, Client *cli);
};