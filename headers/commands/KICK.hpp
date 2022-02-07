/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:17:44 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 14:17:44 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class kick : public command
{
	private:
		bool	_check_Client_nick(std::string cli, channel *chan);
		void	_inform_members(std::string message, channel *chan);
		client*	_get_Client(std::string name, channel *chan);

	public:
		kick();
		~kick();
		void	execute(std::string buf, client *cli, std::vector<channel *> *channels, );
};