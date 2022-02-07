/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:20 by wperu             #+#    #+#             */
/*   Updated: 2022/02/02 15:33:06 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>

class Client
{
    private:
        std::string _nickname;
        std::string _name;
        std::string _truename;
        std::string _password;
        
        sockaddr_in	_address;
        int     _sock_fd;
        bool    _op;
		bool	_register;
        int     _etat;

    
    
    public:
        Client(int sfd, sockaddr_in address);
        ~Client();
        std::string get_nickname() const;
        std::string get_name() const;
        std::string get_truename() const;
		std::string get_ip() const;
        std::string get_pass() const;
		std::string	get_full_prefix() const;
        int         get_sock_fd() const;
        int         get_etat() const;
        bool        get_op() const;
        bool        get_register() const;
        void        set_etat();
        void        set_pass(std::string pass);
        void        set_nickname(std::string nick);
        void        set_name(std::string name);
        void        set_truename(std::string name);
		void		set_register(bool b);
		
		std::string					recv_buffer;
		std::vector<std::string>	send_buffer;
};