#include "ircserver.hpp"

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

int	handle_new_accept(int sock_fd, std::vector<Client> &all_clients)
{
	int					client_sock;
	sockaddr_in			client_addr;
	socklen_t			client_addr_size;

	client_addr_size = sizeof(client_addr);
	if ((client_sock = accept(sock_fd,
		reinterpret_cast<sockaddr *>(&client_addr), &client_addr_size)) == -1)
		return (-1);
	fcntl(client_sock, F_SETFL, O_NONBLOCK);
	std::cout << inet_ntoa(client_addr.sin_addr) << " connecté au fd "
		<< client_sock << std::endl;
	all_clients.push_back(Client(client_sock, client_addr));
	return (client_sock);
}

void	handle_poll_event(std::vector<pollfd> &fds, int poll_ret,
	int const &sock_fd, std::vector<Client> &all_clients)
{
	int		i;
	pollfd	tmp_poll;

	tmp_poll.events = POLLIN;
	i = 0;
	while (poll_ret)
	{
		fds.at(i); // throws exception if we ever get out of range
		if (fds[i].revents & POLLIN)
		{
			if (fds[i].fd == sock_fd)
			{
				if ((tmp_poll.fd = handle_new_accept(sock_fd, all_clients)) == -1)
					perror("accept");
				else
					fds.push_back(tmp_poll);
			}
			else if (fds[i].fd == 0)
				exit(0);
			else if (receive_msg(fds[i].fd, fds, all_clients))
				exit(1);
			poll_ret--;
		}
		if (fds[i].revents & POLLOUT)
		{
			if (send_pending_msg(get_client_from_fd(fds[i].fd, all_clients), fds))
				exit(1);
			poll_ret--;
		}
		i++;
	}
}

int main(void)
{
	int		sock_fd;
	int		poll_ret;
	pollfd	tmp_poll;

	std::vector<pollfd>		fds;
	std::vector<Client>		clients;
	// std::vector<Channel>	channels;


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
		handle_poll_event(fds, poll_ret, sock_fd, clients);
	}
	return (0);
}
