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
		while (end < msg.size() && msg[end] != '\r' && msg[end] != ' ' && msg[end] != '\n')
			end++;
	}
	return (msg.substr(start, end - start));
}

void	pars_msg(std::string msg, std::string &command, std::vector<std::string> &args)
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
	while (i < msg.size() && msg[i] != '\r' && msg[i] != '\n')
	{
		while (msg[i] == ' ')
			i++;
		if (msg[i] != '\r' && msg[i] != '\n')
		{
			args.push_back(extract_word(msg, i));
			i += args[j].size();
			j++;
		}
	}
}

std::string	get_cmd_from_msg(std::string msg)
{
	size_t	i;

	i = 0;
	if (msg[i] == ':')
	{
		while (i < msg.size() && msg[i] != ' ')
			i++;
		while (msg[i] == ' ')
			i++;
	}
	return (extract_word(msg, i));
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
