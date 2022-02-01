#include "ircserver.hpp"

int	send_message_fd(int	dest_fd, const char *msg)
{
	int	send_ret;
	int	total_sent = 0;
	int	msg_len = strlen(msg);

	while (total_sent < msg_len)
	{
		send_ret = send(dest_fd, msg + total_sent, msg_len - total_sent, 0);
		if (send_ret == -1)
		{
			perror("send message fd");
			return (-1);
		}
		total_sent += send_ret;
	}
	return (0);
}

int	send_msg_to_others(int src_fd, int sock_fd,
	std::vector<pollfd> &fds, const char *msg)
{
	std::vector<pollfd>::iterator	it = fds.begin();
	std::vector<pollfd>::iterator	it_end = fds.end();

	while (it != it_end)
	{
		if (it->fd != src_fd && it->fd != sock_fd && it->fd != 0)
		{
			if (send_message_fd(it->fd, msg) == -1)
				return (-1);
		}
		it++;
	}
	return (0);
}

// int	send_pending_msg(pollfd &src_poll, )