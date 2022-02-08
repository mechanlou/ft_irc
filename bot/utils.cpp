#include "bot.hpp"

std::string extract_prefix(std::string msg)
{
	if (msg[0] == ':')
		return (msg.substr(1, msg.find_first_of(' ') - 1));
	return (std::string());
}

std::string	extract_word(std::string msg, size_t &start)
{
	size_t	end;

	if (msg[start] == ':')
	{
		start++;
		end = start;
		while (end < msg.size() && msg[end] != '\r' && msg[end] != '\n')
			end++;
	}
	else
	{
		end = start;
		while (end < msg.size() && msg[end] != '\r' && msg[end] != ' ')
			end++;
	}
	return (msg.substr(start, end - start));
}

void	pars_msg(std::string msg, std::string &command,
	std::vector<std::string> &args)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (msg[i] == ':')
	{
		while (i < msg.size() && msg[i] != ' ')
			i++;
		while (msg[i] == ' ')
			i++;
	}
	command = extract_word(msg, i);
	i += command.size();
	j = 0;
	while (i < msg.size() && msg[i] != '\r')
	{
		while (msg[i] == ' ')
			i++;
		if (msg[i] != '\r')
		{
			args.push_back(extract_word(msg, i));
			i += args[j].size();
			j++;
		}
	}
}

int		recv_entire_msg(int	sock_fd, std::string &msg)
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

int	send_message_fd(int	dest_fd, const char *msg)
{
	int	send_ret;
	int	total_sent = 0;
	int	msg_len = strlen(msg);

	std::cout << "Sending : " << msg;
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
