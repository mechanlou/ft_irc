/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:05:36 by wperu             #+#    #+#             */
/*   Updated: 2022/02/15 15:19:20 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class list : public commands
{
    public:
    list();
    ~list();
    void excute(std::string msg, std::vector<Channel> *all_channels,
		Client *src,std::vector<pollfd> &fds);
};

