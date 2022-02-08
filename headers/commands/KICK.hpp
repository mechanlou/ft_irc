/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:17:44 by wperu             #+#    #+#             */
/*   Updated: 2022/02/08 17:55:05 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class kick : public commands
{
	private:
		bool	_check_Client_nick(std::string cli, Channel *chan);
		Client*	_get_Client(std::string name, Channel *chan);

	public:
		kick();
		~kick();
		void	execute(std::string buf, Client *cli, std::vector<Channel> *channels, std::vector<pollfd> &fds);
};