#pragma once
#include "ircserver.hpp"

class privmsg : public commands
{
    private:

    public:
        void execute(std::string msg, Client *src, std::vector<Channel> all_chans, std::vector<Client> all_clients);
        privmsg();
        ~privmsg();
};
