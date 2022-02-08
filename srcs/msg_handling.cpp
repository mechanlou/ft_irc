#include "ircserver.hpp"
#include "parser.hpp"
int	close_connection(int src_fd, std::vector<pollfd> &fds,
	std::vector<Client> &all_clients, std::vector<Channel> &all_chans)
{
	std::vector<pollfd>::iterator	it_fds = fds.begin();
	std::vector<Client>::iterator	it_clients = all_clients.begin();
	std::vector<Channel>::iterator	it_chans = all_chans.begin();
	std::vector<Channel>::iterator	it_chans_end = all_chans.end();

	while (it_fds->fd != src_fd)
		it_fds++;
	fds.erase(it_fds);
	while (it_clients->get_sock_fd() != src_fd)
		it_clients++;
	while (it_chans != it_chans_end)
	{
		it_chans->remove_user(&(*it_clients));
		it_chans++;
	}
	all_clients.erase(it_clients);
	if (close(src_fd))
	{
		perror("close fd (what)");
		return (-1);
	}
	return (0);
}

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
	std::vector<Client> &all_clients, std::vector<Channel> &all_channels)
{
	// std::ostringstream				to_send;
	parser							tool;
	int								recv_ret;
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
		std::cout << src_fd << " déconnecté" << std::endl;
		return (close_connection(src_fd, fds, all_clients, all_channels));
	}
	else
	{
		src_client.recv_buffer += received_msg;
		if (received_msg.find_first_of(END_OF_MSG) != std::string::npos)
		{
			received_msg = src_client.recv_buffer;
			src_client.recv_buffer.clear();
			tool.parse(received_msg, &get_client_from_fd(src_fd, all_clients),
				&all_clients, &all_channels, fds); // parse call
			// to_send << src_fd << " : " << received_msg;
			// std::cout << to_send.str();
			// send_msg_to_others(src_fd, all_clients, fds, (to_send.str()).c_str());
		}
	}
	return (0);
}
