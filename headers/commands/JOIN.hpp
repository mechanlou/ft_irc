/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:55:27 by wperu             #+#    #+#             */
/*   Updated: 2022/02/03 16:26:37 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commands.hpp"

class join : public commands
{
    private:

      //  void join_chan(std::string name, client *cli, std::vector<channel *> *chan);
    public:
       // void execute(std::string argument, Client *client, std::vector<channel *> *chan);
        join(){};
        ~join(){};
};
/*
void JOIN::excute(std::string argument, Client *client, std::vector<channel *> *chan)
{
    if(argument == "#")
    {
        std::string tmp = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + client->get_nickname() + " :Join :Not enough parameters\r\n";
        send(client->get_sock_fd, tmp,c_str(), tmp.lenght(), 0);
        return;
    }
    
    int space = argument.find(' ');
    
}*/
