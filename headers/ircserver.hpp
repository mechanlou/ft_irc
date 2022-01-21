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
#include "Channel.hpp"


#define QUEUE_LEN 5
#define BUFFER_SIZE 10
#define PORT "1995"
#define PASSWORD "coucou"
struct	Client
{
	int			sock_fd;
	std::string	nickname;
	// std::string	username;
	// bool	is_operator;
};

class	Channel;

int	receive_msg(int src_fd, int sock_fd, std::vector<pollfd> &fds);
int	send_msg_to_others(int src_fd, int sock_fd,
	std::vector<pollfd> &fds, const char *msg);
int	send_message_fd(int	dest_fd, const char *msg);
