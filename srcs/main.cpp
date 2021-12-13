#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

#define QUEUE_LEN 5
#define BUFFER_SIZE 100
#define PORT "1995"

int main(void)
{
	int					sock;
	int					client_sock;
	addrinfo			hints;
	addrinfo			*serv_info;
	sockaddr_storage	client_addr;
	socklen_t			client_addr_size;
	char				buff[BUFFER_SIZE];
	int					recv_ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, PORT, &hints, &serv_info))
	{
		std::cerr << "Struct error" << std::endl;
		return (1);
	}
	if ((sock = socket(serv_info->ai_family,
		serv_info->ai_socktype, serv_info->ai_protocol)) == -1)
	{
		std::cerr << "Socket error" << std::endl;
		return (1);
	}
	if (bind(sock, serv_info->ai_addr, serv_info->ai_addrlen) == -1)
	{
		std::cerr << "Bind error" << std::endl;
		return (1);
	}
	if (listen(sock, QUEUE_LEN) == -1)
	{
		std::cerr << "Listen error" << std::endl;
		return (1);
	}
	client_addr_size = sizeof(client_addr);
	if ((client_sock = accept(sock,
		reinterpret_cast<sockaddr *>(&client_addr), &client_addr_size)) == -1)
	{
		std::cerr << strerror(client_sock) << std::endl;
		return (1);
	}

	while ((recv_ret = recv(client_sock, buff, BUFFER_SIZE - 1, 0)) > 0)
	{
		buff[recv_ret] = '\0';
		std::cout << buff;
		if (send(client_sock, "Message reçu\n", 14, 0) == -1)
		{
			std::cerr << "send error" << std::endl;
			return (1);
		}
	}
	std::cout << "Voila :/" << std::endl;
	freeaddrinfo(serv_info);
	return (0);
}
