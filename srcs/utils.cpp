#include "ircserver.hpp"

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

msg_content	pars_msg(std::string msg)
{
	size_t	i;
	size_t	j;
	msg_content	content;

	i = 0;
	if (msg[i] == ':')
	{
		while (i < msg.size() && msg[i] != ' ')
			i++;
		while (msg[i] == ' ')
			i++;
	}
	content.command = extract_word(msg, i);
	i += content.command.size();
	j = 0;
	while (i < msg.size() && msg[i] != '\r')
	{
		while (msg[i] == ' ')
			i++;
		if (msg[i] != '\r')
		{
			content.args.push_back(extract_word(msg, i));
			i += content.args[j].size();
			j++;
		}
	}
	return (content);
}

Client	&get_client_from_fd(int src_fd, std::vector<Client> &clients)
{
	std::vector<Client>::iterator	it = clients.begin();
	std::vector<Client>::iterator	end = clients.end();

	while (it != end)
	{
		if (it->get_sock_fd() == src_fd)
			return (*it);
		it++;
	}
	throw (std::exception());
	return (*it);
}
