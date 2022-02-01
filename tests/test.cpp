#include <string>
#include <vector>
#include <iostream>

struct msg_content
{
	std::string					command;
	std::vector<std::string>	args;
};

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


int main(void)
{
	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator it_end;
	msg_content content = pars_msg(":labite COMAND dacor ok oui :ah oui dacor");

	std::cout << "command : |" << content.command << '|' << std::endl;
	std::cout << "args :" << std::endl;
	it = content.args.begin();
	it_end = content.args.end();
	while (it != it_end)
	{
		std::cout << "|" << *it << "|" << std::endl;
		it++;
	}
	return (0);
}