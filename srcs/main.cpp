#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

int main(void)
{
	int			sock;
	addrinfo	hints;
	addrinfo	*serv_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, "1995", &hints, &serv_info))
	{
		std::cerr << "Struct error" << std::endl;
		return (1);
	}
	for (addrinfo *tmp = serv_info; tmp != NULL; tmp = tmp->ai_next)
	{
		std::cout <<
		inet_ntoa(reinterpret_cast<sockaddr_in *>(tmp->ai_addr)->sin_addr)
		<< std::endl;
	}
	// std::cout << serv_info->ai_protocol << std::endl;
	if ((sock = socket(serv_info->ai_family,
		serv_info->ai_socktype,serv_info->ai_protocol)) == -1)
	{
		std::cerr << "Socket error" << std::endl;
		return (1);
	}
	if ()

	std::cout << "Voila :/" << std::endl;
	freeaddrinfo(serv_info);
	return (0);
}