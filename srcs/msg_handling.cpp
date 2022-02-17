#include "ircserver.hpp"
#include "parser.hpp"

int	close_connection(int src_fd, std::vector<pollfd> &fds,
	std::vector<Client *> &all_clients, std::vector<Channel> &all_chans)
{
	std::vector<pollfd>::iterator	it_fds = fds.begin();
	std::vector<Client *>::iterator	it_clients = all_clients.begin();
	std::vector<Channel>::iterator	it_chans = all_chans.begin();
	std::vector<Channel>::iterator	it_chans_end = all_chans.end();
	std::string				part_msg;
	Client					*cli;

	while (it_fds->fd != src_fd)
		it_fds++;
	fds.erase(it_fds);
	while ((*it_clients)->get_sock_fd() != src_fd)
		it_clients++;
	cli = *it_clients;
	while (it_chans != it_chans_end)
	{
		if (it_chans->remove_user(cli))
		{
			part_msg = ":" + cli->get_nickname() + "!" +
				cli->get_truename() + cli->get_ip() + " PART " +
				it_chans->get_name() + ":" + "bye" + END_OF_MSG;
			it_chans->msg_to_channel(part_msg.c_str(), fds);
			if (it_chans->get_all_users().size() == 0)
			{
				all_chans.erase(it_chans);
				it_chans = all_chans.begin();
				it_chans_end = all_chans.end();
			}
			else
			{
				if (it_chans->get_operators().size() == 0)
				{
					it_chans->add_operator_user(it_chans->get_all_users()[0]);
					rpl_youreoper(it_chans->get_operators().back(), fds);
				}
				it_chans++;
			}
		}
		else
			it_chans++;
	}
	all_clients.erase(it_clients);
	delete cli;
	if (close(src_fd))
	{
		perror("close fd (what)");
		return (-1);
	}
	std::cout << src_fd << " déconnecté" << std::endl;
	return (1);
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

std::string	get_next_msg(std::string &buffer)
{
	std::string	new_msg;
	size_t		eom_pos;

	eom_pos = buffer.find(END_OF_MSG);
	if (eom_pos != buffer.npos)
		eom_pos += 2;
	new_msg = buffer.substr(0, eom_pos);
	buffer.erase(0, eom_pos);
	return (new_msg);
}

int	receive_msg(int src_fd, std::vector<pollfd> &fds,
	std::vector<Client *> &all_clients, std::vector<Channel> &all_channels)
{
	parser		tool;
	int			recv_ret;
	std::string	received_msg;
	Client		*src_client = get_client_from_fd(src_fd, all_clients);

	recv_ret = recv_entire_msg(src_fd, &received_msg);
	if (recv_ret < 0)
	{
		perror("recv");
		return (-1);
	}
	else if (!recv_ret)
		return (close_connection(src_fd, fds, all_clients, all_channels));
	else
	{
		src_client->recv_buffer += received_msg;
		if (src_client->recv_buffer.find(END_OF_MSG) != std::string::npos)
		{
			received_msg = get_next_msg(src_client->recv_buffer);
			std::cout << "<-- [" << src_client->get_nickname();
			std::cout <<  "] : " << received_msg;
			tool.parse(received_msg, get_client_from_fd(src_fd, all_clients),
				&all_clients, &all_channels, fds); // parse call
		}
	}
	return (0);
}
