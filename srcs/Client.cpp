/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:32:11 by wperu             #+#    #+#             */
/*   Updated: 2022/01/31 14:05:16 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

Client::Client(int sfd, sockaddr_in address)
{
    _sock_fd = sfd;
    _address = address;
    _register = false;
}

Client::~Client()
{
    
}

std::string Client::get_nickname()
{
    return(_nickname);
}

std::string Client::get_name()
{
    return(_name);
}

std::string Client::get_truename()
{
    return(_truename);
}

std::string Client::get_ip()
{
    std::string ip = inet_ntoa(_address.sin_addr);
    return (ip);
}

int Client::get_sock_fd()
{
    return(_sock_fd);
}

bool Client::get_op()
{
    return(_op);
}

void Client::set_nickname(std::string nick)
{
    _nickname = nick;
}

void Client::set_name(std::string name)
{
    _name = name;
}

void Client::set_truename(std::string truename)
{
    _truename = truename;
}

void Client::set_register()