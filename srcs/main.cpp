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

#define QUEUE_LEN 5
#define BUFFER_SIZE 100
#define PORT "1995"

int	get_listen_sock_fd(void)
{
	int					sock_fd;
	addrinfo			hints;
	addrinfo			*serv_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, PORT, &hints, &serv_info))
	{
		std::cerr << "Struct error" << std::endl;
		return (-1);
	}
	if ((sock_fd = socket(serv_info->ai_family,
		serv_info->ai_socktype, serv_info->ai_protocol)) == -1)
	{
		freeaddrinfo(serv_info);
		std::cerr << "Socket error" << std::endl;
		return (-1);
	}
	fcntl(sock_fd, F_SETFL, O_NONBLOCK);
	if (bind(sock_fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1)
	{
		freeaddrinfo(serv_info);
		std::cerr << "Bind error" << std::endl;
		return (-1);
	}
	if (listen(sock_fd, QUEUE_LEN) == -1)
	{
		freeaddrinfo(serv_info);
		std::cerr << "Listen error" << std::endl;
		return (-1);
	}
	freeaddrinfo(serv_info);
	return (sock_fd);
}

int	handle_new_accept(int sock_fd)
{
	int					client_sock;
	sockaddr_storage	client_addr;
	socklen_t			client_addr_size;

	client_addr_size = sizeof(client_addr);
	if ((client_sock = accept(sock_fd,
		reinterpret_cast<sockaddr *>(&client_addr), &client_addr_size)) == -1)
	{
		// std::cerr << strerror(client_sock) << std::endl;
		return (-1);
	}
	fcntl(client_sock, F_SETFL, O_NONBLOCK);
	
	if (send(client_sock, "Connecté\n", 10, 0) == -1)
	{
		std::cerr << "send \"Connecté\" error" << std::endl;
		return (-1);
	}
	return (client_sock);
}

int	send_msg_to_others(int src_fd, int sock_fd, std::vector<pollfd> &fds, std::string msg)
{
	std::vector<pollfd>::iterator	it = fds.begin();
	std::vector<pollfd>::iterator	it_end = fds.end();

	while (it != it_end)
	{
		if ((*it).fd != src_fd && (*it).fd != sock_fd && (*it).fd != 0)
		{
			if (send((*it).fd, msg.c_str(), msg.size(), 0) == -1)
			{
				std::cout << strerror(errno) << std::endl;
				return (-1);
			}
		}
		it++;
	}
	return (0);
}

int	read_msg_from_fd(int src_fd, int sock_fd, std::vector<pollfd> &fds)
{
	char							buff[BUFFER_SIZE];
	int								recv_ret;
	std::vector<pollfd>::iterator	it;
	std::ostringstream				msg;
	
	recv_ret = recv(src_fd, buff, BUFFER_SIZE - 1, 0);
	if (recv_ret < 0)
		return (-1);
	else if (!recv_ret)
	{
		it = fds.begin();
		while ((*it).fd != src_fd)
			it++;
		fds.erase(it);
		if (close(src_fd))
		{
			std::cerr << "close error (how ?)" << std::endl;
			return (-1);
		}
		std::cout << src_fd << " déconnecté" << std::endl;
	}
	else
	{
		buff[recv_ret] = '\0';
		msg << src_fd << " : " << buff;
		std::cout << msg.str();
		if (send_msg_to_others(src_fd, sock_fd, fds, msg.str()) == -1)
		{
			std::cerr << "send error" << std::endl;
			return (-1);
		}
	}
	return (0);
}

int main(void)
{
	int		sock_fd;
	int		poll_ret;
	int		i;
	pollfd	tmp_poll;
	std::vector<pollfd>	fds;
	
	if ((sock_fd = get_listen_sock_fd()) == -1)
		return (1);
	tmp_poll.fd = sock_fd;
	tmp_poll.events = POLLIN;
	fds.push_back(tmp_poll);
	tmp_poll.fd = 0;
	fds.push_back(tmp_poll);
	while (1)
	{
		if ((poll_ret = poll(&fds[0], fds.size(), -1)) == -1)
		{
			std::cerr << "poll error wtf bruh" << std::endl;
			return (1);
		}
		i = 0;
		while (poll_ret)
		{
			fds.at(i);
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == sock_fd)
				{
					if ((tmp_poll.fd = handle_new_accept(sock_fd)) == -1)
						perror("accept");
					else
					{
						fds.push_back(tmp_poll);
						std::cout << tmp_poll.fd << " connecté" << std::endl;
					}
				}
				else if (fds[i].fd == 0)
					return (0);
				else if (read_msg_from_fd(fds[i].fd, sock_fd, fds))
					return (1);
				poll_ret--;
			}
			i++;
		}
	}
	
	std::cout << "Voila :/" << std::endl;
	return (0);
}
