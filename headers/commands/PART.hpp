/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:19:05 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 13:19:05 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class part : public command
{

	public:
		part();
		~part();
		void	execute(std::string buf, client *cli, std::vector<channel *> *chan, std::vector<pollfd> &fds);
};