#include "ircserver.hpp"

int	recv_entire_msg(int	src_fd, std::string *msg)
{
	int		recv_ret;
	char	buff[BUFFER_SIZE];

	do
	{
		recv_ret = recv(src_fd, buff, BUFFER_SIZE - 1, 0);
		if (recv_ret > 0)
		{
			buff[recv_ret] = '\0';
			*msg += buff;
		}
	}
	while (recv_ret > 0 && !strchr(buff, '\n'));
	return (recv_ret);
}

int	receive_msg(int src_fd, int sock_fd, std::vector<pollfd> &fds)
{
	int								recv_ret;
	std::vector<pollfd>::iterator	it;
	std::ostringstream				to_send;
	std::string						received_msg;
	
	recv_ret = recv_entire_msg(src_fd, &received_msg);
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
		to_send << src_fd << " : " << received_msg;
		std::cout << to_send.str();
		if (send_msg_to_others(src_fd, sock_fd, fds, (to_send.str()).c_str()) == -1)
		{
			std::cerr << "send error" << std::endl;
			return (-1);
		}
	}
	return (0);
}
