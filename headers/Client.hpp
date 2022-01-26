/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:20 by wperu             #+#    #+#             */
/*   Updated: 2022/01/26 16:48:40 by wperu            ###   ########lyon.fr   */
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
        
        
        std::vector<std::string> *invit;
        sockaddr_in	_address;
        int     _sock_fd;
        bool    _op;
		bool	_register;
    
    public:
        Client(int sfd, sockaddr_in address);
        ~Client();
        std::string get_nickname();
        std::string get_name();
        std::string get_truename();
		std::string get_ip();
        int         get_sock_fd();
        bool        get_op();
        void        set_nickname(std::string nick);
        void        set_name(std::string name);
        void        set_truename(std::string name);
		void		set_register(bool b);
		void		add_chan_inv(std::string chan);
		bool		is_invited(std::string chan);
 
};