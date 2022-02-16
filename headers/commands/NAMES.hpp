/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:10:27 by wperu             #+#    #+#             */
/*   Updated: 2022/02/16 17:00:22 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class names : public commands
{
    public:
        names();
        ~names();
        void	excute(std::string buf,Client *cli, std::vector<Channel> *chan,
			std::vector<Client *> *all_clients, std::vector<pollfd> &fds);
};