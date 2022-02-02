#include "ircserver.hpp"

int	recv_entire_msg(int	src_fd, std::string *msg)
{
	int		recv_ret;
	char	buff[BUFFER_SIZE];

	recv_ret = recv(src_fd, buff, BUFFER_SIZE - 1, 0);
	if (recv_ret > 0)
	{
		buff[recv_ret] = '\0';
		*msg += buff;
	}
	return (recv_ret);
}

int	receive_msg(int src_fd, std::vector<pollfd> &fds,
	std::vector<Client> &all_clients) // NEED TO REDO DISCONNECTIONS
{
	std::vector<pollfd>::iterator	it;
	int								recv_ret;
	std::ostringstream				to_send;
	std::string						received_msg;
	Client				&src_client = get_client_from_fd(src_fd, all_clients);
	
	recv_ret = recv_entire_msg(src_fd, &received_msg);
	if (recv_ret < 0)
	{
		perror("recv");
		return (-1);
	}
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
		src_client.recv_buffer += received_msg;
		if (received_msg.find_first_of(END_OF_MSG) != std::string::npos)
		{
			received_msg = src_client.recv_buffer;
			src_client.recv_buffer.clear();
			to_send << src_fd << " : " << received_msg;
			std::cout << to_send.str();
			send_msg_to_others(src_fd, all_clients, fds, (to_send.str()).c_str());
		}
	}
	return (0);
}
