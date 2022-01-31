/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:55:27 by wperu             #+#    #+#             */
/*   Updated: 2022/01/26 17:02:23 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

class JOIN : public commands
{
    private:

        void join_chan(std::string name, client *cli, std::vector<channel *> *chan)
    public:
        void execute(std::string argument, Client *client, std::vector<channel *> *chan);
        JOIN()
        ~JOIN();
}

void JOIN::excute(std::string argument, Client *client, std::vector<channel *> *chan)
{
    if(argument == "#")
    {
        std::string tmp = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + client->get_nickname() + " :Join :Not enough parameters\r\n";
        send(client->get_sock_fd, tmp,c_str(), tmp.lenght(), 0);
        return;
    }
    
    int space = argument.find(' ');
    
}