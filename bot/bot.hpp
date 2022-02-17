#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <fcntl.h>

#include <iostream>

#define BUFFER_SIZE 10
#define EOM	"\n"
#define NICKNAME "nicebot"

void		pars_msg(std::string msg, std::string &command,
	std::vector<std::string> &args);
int			send_message_fd(int	dest_fd, const char *msg);
int			recv_entire_msg(int	sock_fd, std::string &msg);
void		server_listen_loop(int sock_fd, char *chan);
int			connect_to_server(int sock_fd, char *pass, char *chan);
std::string extract_prefix(std::string msg);
