#include "ircserver.hpp"

void	send_msg_client(Client *dst, std::vector<pollfd> &fds, const char *msg)
{
	int	i;

	dst->send_buffer.push_back(msg);
	i = 0;
	// std::cout << "fds size : " << fds.size() << std::endl;
	while (fds[i].fd != dst->get_sock_fd())
	{
		// std::cout << "i : " << i << std::endl;
		i++;
	}
	fds[i].events = POLLIN | POLLOUT;
}

void	send_msg_to_others(int src_fd, std::vector<Client *> &all_clients,
	std::vector<pollfd> &fds, const char *msg)
{
	std::vector<Client *>::iterator	it = all_clients.begin();
	std::vector<Client *>::iterator	it_end = all_clients.end();

	while (it != it_end)
	{
		if ((*it)->get_sock_fd() != src_fd)
			send_msg_client(*it, fds, msg);
		it++;
	}
}

int	broadcast_msg(std::vector<Client *> &all_clients,
	std::vector<pollfd> &fds, const char *msg)
{
	std::vector<Client *>::iterator	it = all_clients.begin();
	std::vector<Client *>::iterator	it_end = all_clients.end();

	while (it != it_end)
	{
		send_msg_client(*it, fds, msg);
		it++;
	}
	return (0);
}

int	send_pending_msg(Client *dst, std::vector<pollfd> &fds)
{
	ssize_t	send_ret;
	size_t	i;
	int		fd;

	send_ret = send(dst->get_sock_fd(), dst->send_buffer[0].c_str(),
		dst->send_buffer[0].size(), 0);
	if (send_ret == -1)
	{
		perror("send pending msg");
		return (-1);
	}
	else if (send_ret >= static_cast<ssize_t>(dst->send_buffer[0].size()))
		dst->send_buffer.erase(dst->send_buffer.begin());
	else
		dst->send_buffer[0].erase(0, send_ret);
	i = 0;
	fd = dst->get_sock_fd();
	while (fds[i].fd != fd)
		i++;
	if (dst->send_buffer.empty())
		fds[i].events = POLLIN;
	else
		fds[i].events = POLLIN | POLLOUT;
	return (0);
}