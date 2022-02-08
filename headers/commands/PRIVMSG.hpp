#pragma once
#include "ircserver.hpp"

class privmsg : public commands
{
    private:
		void	_send_channel(std::string msg, Client *src,
			std::vector<Channel> *all_chans, std::vector<pollfd> &fds,
			std::vector<std::string> args);
		void	_send_client(std::string msg, Client *src,
			std::vector<Client> *all_clients, std::vector<pollfd> &fds,
			std::vector<std::string> args);

    public:
        void	execute(std::string msg, Client *src,
			std::vector<Channel> *all_chans, std::vector<Client> *all_clients,
			std::vector<pollfd> &fds);
        privmsg();
        ~privmsg();
};
