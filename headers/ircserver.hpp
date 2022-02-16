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
#include <stdio.h>
#include "reply_codes.hpp"
#include "reply_functions.hpp"
#include "commands/commands.hpp"
#include "Channel.hpp"

#define	END_OF_MSG "\r\n" //a remplacer par "\r\n" pour IRC
#define QUEUE_LEN 5
#define BUFFER_SIZE 10

#define	HOSTNAME NULL
#define SERV_NAME "irc.tamere.net"
#define VERSION "6.6.7"
#define	START_DATE "not long ago acutally"
#define PROTOCOLE_VERSION "2.9"

extern char	*g_password;

class			ReplyDoesntExistException : public std::exception
{
	public :

	virtual const char	*what(void) const throw()
	{
		return ("Error, reply doesn't exist");
	}
};

// class	Channel;

int			receive_msg(int src_fd,	std::vector<pollfd> &fds,
	std::vector<Client *> &all_clients, std::vector<Channel> &all_channels);
void		add_crlf(std::string &msg);
void		pars_msg(std::string msg, std::string &command,
	std::vector<std::string> &args);
int			broadcast_msg(std::vector<Client *> &all_clients,
	std::vector<pollfd> &fds, const char *msg); // POUR BROADCAST UN MSG
void		send_msg_to_others(int src_fd, std::vector<Client *> &all_clients,
	std::vector<pollfd> &fds, const char *msg); // POUR BROADCAST SAUF A UN CLIENT
void		send_msg_client(Client *dst, std::vector<pollfd> &fds,
	const char *msg);	//FONCTION A UTILISER POUR ENOVYER UN MESSAGE
int			send_pending_msg(Client *dst, std::vector<pollfd> &fds);
Client		*get_client_from_fd(int src_fd, std::vector<Client *> &clients);
int			close_connection(int src_fd, std::vector<pollfd> &fds,
	std::vector<Client *> &all_clients, std::vector<Channel> &all_chans);
std::string	get_cmd_from_msg(std::string msg);
void		print_all_clients_infos(std::vector<Client *> const &all_clients);
