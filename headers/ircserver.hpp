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
#include "Channel.hpp"
#include "reply_codes.hpp"
#include "reply_functions.hpp"
#include "commands/commands.hpp"


#define QUEUE_LEN 5
#define BUFFER_SIZE 10
#define PORT "1995"

#define SERV_NAME "irc.tamere.net"
#define VERSION "6.6.7"
#define	START_DATE "not long ago acutally"
#define PROTOCOLE_VERSION "2.9"

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
int			receive_msg(int src_fd, int sock_fd, std::vector<pollfd> &fds,
	std::vector<Channel> &channels);
int			send_msg_to_others(int src_fd, int sock_fd,
	std::vector<pollfd> &fds, const char *msg);
int			send_message_fd(int	dest_fd, const char *msg);
void		add_crlf(std::string &msg);
msg_content	pars_msg(std::string msg);
