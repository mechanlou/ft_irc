#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <ctime>
#include <algorithm>
#include "reply_codes.hpp"
#include "reply_functions.hpp"
#include "commands/commands.hpp"
#include "Channel.hpp"
// #include "parser.hpp"

#define	END_OF_MSG "\n" //a remplacer par "\n\r" pour IRC
#define QUEUE_LEN 5
#define BUFFER_SIZE 10
#define PORT "6667"
#define PASSWORD "bonjour"

#define SERV_NAME "irc.tamere.net"
#define VERSION "6.6.7"
#define	START_DATE "not long ago acutally"
#define PROTOCOLE_VERSION "2.9"


class parser;

struct msg_content
{
	std::string					command;
	std::vector<std::string>	args;
};

class			ReplyDoesntExistException : public std::exception
{
	public :

	virtual const char	*what(void) const throw()
	{
		return ("Error, reply doesn't exist");
	}
};

class	Channel;

int			receive_msg(int src_fd,	std::vector<pollfd> &fds,
	std::vector<Client> &all_clients, std::vector<Channel> &all_channels);
void		add_crlf(std::string &msg);
msg_content	pars_msg(std::string msg);
int			broadcast_msg(std::vector<Client> &all_clients,
	std::vector<pollfd> &fds, const char *msg); // POUR BROADCAST UN MSG
void		send_msg_to_others(int src_fd, std::vector<Client> &all_clients,
	std::vector<pollfd> &fds, const char *msg); // POUR BROADCAST SAUF A UN CLIENT
void		send_msg_client(Client &dst, std::vector<pollfd> &fds,
	const char *msg);	//FONCTION A UTILISER POUR ENOVYER UN MESSAGE
int			send_pending_msg(Client &dst, std::vector<pollfd> &fds);
Client		&get_client_from_fd(int src_fd, std::vector<Client> &clients);