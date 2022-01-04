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
#include "Channel.hpp"

#define QUEUE_LEN 5
#define BUFFER_SIZE 10
#define PORT "1995"

class			ReplyDoesntExistException : public std::exception
{
	public :

	virtual const char	*what(void) const throw()
	{
		return ("Error, reply doesn't exist");
	}
};

struct	Client
{
	int			sock_fd;
	char		registration_status;
	// -> 0 = juste socket connecté, 1 = reçu PASS, 2 = reçu NICK, 3 = reçu USER

	std::string	nickname;
	std::string	real_name;
	int			mode;
	// bool	is_operator;

	// bool	operator==(Client const &other)
	// {
	// 	if (sock_fd == other.sock_fd && nickname == other.nickname
	// 		&& real_name == other.real_name
	// 		&& registration_status == other.registration_status
	// 		&& mode = other.mode)
	// 		return (true);
	// 	return (false);
	// }
};

class	Channel;

int	receive_msg(int src_fd, int sock_fd, std::vector<pollfd> &fds,
	std::vector<Channel> &channels);
int	send_msg_to_others(int src_fd, int sock_fd,
	std::vector<pollfd> &fds, const char *msg);
int	send_message_fd(int	dest_fd, const char *msg);
