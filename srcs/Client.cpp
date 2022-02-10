/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:32:11 by wperu             #+#    #+#             */
/*   Updated: 2022/02/10 18:01:41 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

Client::Client(int sfd, sockaddr_in address)
{
    _sock_fd = sfd;
    _address = address;
    _register = false;
    _op = false;
    _etat = 0;
}

Client::~Client()
{
    
}

std::string Client::get_nickname() const
{
    return(_nickname);
}

std::string Client::get_name() const
{
    return(_name);
}

std::string Client::get_truename() const
{
    return(_truename);
}

std::string Client::get_ip() const
{
    std::string ip = inet_ntoa(_address.sin_addr);
    return (ip);
}

std::string Client::get_pass() const
{
    return(_password);
}

std::string	Client::get_full_prefix() const //with ':' and space at the end
{
	std::string	prefix(":");

	prefix += _nickname;
	prefix += '!';
	prefix += _name;
	prefix += '@';
	prefix += get_ip();
	prefix += ' ';
	return (prefix);
}


int Client::get_sock_fd() const
{
    return(_sock_fd);
}

bool Client::get_op() const
{
    return(_op);
}

bool Client::get_register() const
{
    return(_register);
}

int Client::get_etat() const
{
    return(_etat);
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

void Client::set_register(bool b)
{
	_register = b;
}

void Client::set_pass(std::string pass)
{
    _password = pass;
}

void Client::set_etat()
{
    _etat = 1;
}