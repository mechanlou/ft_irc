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
	struct timeval tv;

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
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO,
				reinterpret_cast<const char*>(&tv), sizeof tv))
				perror("setsockopt");
			else if (connect(sock_fd, tmp->ai_addr, tmp->ai_addrlen) != -1)
				break;
			if (close(sock_fd))
				perror("close (wat?)");
		}
		tmp = tmp->ai_next;
	}
	if (tmp == NULL)
	{
		std::cout << "Couldn't connect to " << IP << ':' << port << std::endl;
		sock_fd = -1;
	}
	else
		std::cout << "Successfully connected to " << inet_ntop(tmp->ai_family,
		get_sin_addr(tmp->ai_addr), buff, INET6_ADDRSTRLEN) << ':' << port <<
		std::endl;
	freeaddrinfo(serv_info);
	return (sock_fd);
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
	if (connect_to_server(sock_fd, argv[3], argv[4]))
		return (1);
	server_listen_loop(sock_fd, argv[4]);
	return (0);
}