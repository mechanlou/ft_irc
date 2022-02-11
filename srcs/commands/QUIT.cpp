/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:18 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 12:07:18 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/QUIT.hpp"

quit::quit()
{
}

quit::~quit()
{
}

int	quit::excute(std::string buf, Client *cli, std::vector<Channel> *chan, std::vector<Client> *clients,std::vector<pollfd> &fds)
{
	std::string	announcement;

	announcement = ":" + cli->get_nickname() + "!" + cli->get_name() + "@" + cli->get_ip() + ' ' + buf;
	broadcast_msg(*clients, fds, announcement.c_str());
	return (close_connection(cli->get_sock_fd(), fds, *clients, *chan));
}