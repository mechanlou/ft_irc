#include "bot.hpp"
// ./nicebot <IP> <PORT> <PASSWORD> <CHANNEL>

void *get_sin_addr(struct sockaddr *ai_addr)
{
	if (ai_addr->sa_family == AF_INET)
		return &((reinterpret_cast<sockaddr_in *>(ai_addr))->sin_addr);
	return &((reinterpret_cast<sockaddr_in6 *>(ai_addr))->sin6_addr);
}

int	get_sock_fd(char *IP, char *port)
{
	int			sock_fd;
	addrinfo	hints, *serv_info, *tmp;
	char		buff[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(IP, port, &hints, &serv_info))
	{
		std::cerr << "Bad IP or port" << std::endl;
		return (-1);
	}
	tmp = serv_info;
	while (tmp != NULL)
	{
		if ((sock_fd = socket(tmp->ai_family, tmp->ai_socktype,
			tmp->ai_protocol)) != -1)
		{
			if (connect(sock_fd, tmp->ai_addr, tmp->ai_addrlen) != -1)
				break;
			if (close(sock_fd))
				perror("close (wat?)");
		}
		tmp = tmp->ai_next;
	}
	if (tmp == NULL)
		std::cout << "Couldn't connect to " << IP << ':' << port << std::endl;
	else
		std::cout << "Successfully connected to " << inet_ntop(tmp->ai_family,
		get_sin_addr(tmp->ai_addr), buff, INET6_ADDRSTRLEN) << ':' << port <<
		std::endl;
	freeaddrinfo(serv_info);
	return (sock_fd);
}

int	recv_entire_msg(int	sock_fd, std::string &msg)
{
	int		recv_ret;
	char	buff[BUFFER_SIZE];

	do
	{
		recv_ret = recv(sock_fd, buff, BUFFER_SIZE - 1, 0);
		if (recv_ret > 0)
		{
			buff[recv_ret] = '\0';
			msg += buff;
		}
	}
	while (recv_ret > 0 && !strstr(buff, EOM));
	return (recv_ret);
}

int	listen_to_server(int sock_fd)
{
	int			recv_ret;
	std::string	msg;

	do
	{
		recv_ret = recv_entire_msg(sock_fd, msg);
		if (recv_ret > 0)
			std::cout << msg;
		msg.clear();
	}
	while (recv_ret > 0);
	return (0);
}

int main(int argc, char **argv)
{
	int	sock_fd;

	if (argc != 5)
	{
		std::cerr << "Usage : ./nicebot <IP> <PORT> <PASSWORD> <CHANNEL>"
			<< std::endl;
		return (1);
	}
	sock_fd = get_sock_fd(argv[1], argv[2]);
	if (sock_fd < 0)
		return (1);
	return (listen_to_server(sock_fd));
}