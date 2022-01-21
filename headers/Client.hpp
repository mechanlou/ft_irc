/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:20 by wperu             #+#    #+#             */
/*   Updated: 2022/01/21 10:05:13 by wperu            ###   ########lyon.fr   */
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
        
        std::vector<std::string> *invit;
        
        int     _sock_fd;
        bool    _op;
    
    public:
        std::string get_nickname();
        std::string get_name();
        int         get_sock_fd();
        bool        get_op();
        void        set_nickname(std::string nick);
        void        set_name(std::string name);
        
 
};