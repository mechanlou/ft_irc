#include "bot.hpp"

int	process_msg(int sock_fd, std::string msg, char *chan)
{
	std::string					prefix(extract_prefix(msg));
	std::string					cmd;
	std::vector<std::string>	args;
	std::string					target_nick;
	std::string					answer("NOTICE ");

	answer += chan;
	answer += " :";
	pars_msg(msg, cmd, args);
	if (!prefix.empty())
		target_nick = prefix.substr(0,prefix.find_first_of('!'));
	if (cmd == "JOIN" && target_nick != NICKNAME)
	{
		answer += "Hi ";
		answer += target_nick;
		answer += " !";
		answer += EOM;
		return (send_message_fd(sock_fd, answer.c_str()));
	}
	if (cmd == "PART" && target_nick != NICKNAME)
	{
		answer += "Cya later ";
		answer += target_nick;
		answer += " (never hopefully)";
		answer += EOM;
		return (send_message_fd(sock_fd, answer.c_str()));
	}
	return (0);
}

void	server_listen_loop(int sock_fd, char *chan)
{
	int			recv_ret;
	std::string	msg;

	do
	{
		recv_ret = recv_entire_msg(sock_fd, msg);
		if (recv_ret < 0 && errno != EAGAIN)
		{
			recv_ret = 0;
			perror("listen loop");
		}
		if (recv_ret > 0 && process_msg(sock_fd, msg, chan))
			recv_ret = 0;
		errno = 0;
		msg.clear();
	}
	while (recv_ret != 0);
}

int	recv_answer(int sock_fd, std::string step)
{
	int			ret;
	std::string	msg;

	if ((ret = recv_entire_msg(sock_fd, msg)) <= 0)
	{
		if (ret == 0)
		{
			std::cerr << "Connection lost" << std::endl;
			return (-1);
		}
		if (ret == -1 && errno != EAGAIN)
		{
			perror(step.c_str());
			return (-1);
		}
		errno = 0;
		std::cout << "No answer" << std::endl;
	}
	else
	{
		std::cout << "Received : " << msg;
		std::cerr << step << " error" << std::endl;
		return (-1);
	}
	return (0);
}

int	recv_answer_join(int sock_fd)
{
	int							ret;
	std::string					msg;
	std::string					cmd;
	std::vector<std::string>	args;

	do
	{
		if ((ret = recv_entire_msg(sock_fd, msg)) <= 0)
		{
			if (ret == 0)
			{
				std::cerr << "Connection lost" << std::endl;
				return (-1);
			}
			if (ret == -1 && errno != EAGAIN)
			{
				perror("Join");
				return (-1);
			}
			errno = 0;
			std::cout << "No answer" << std::endl;
		}
		else
		{
			pars_msg(msg, cmd, args);
			std::cout << "Received : " << msg;
			if (cmd != "JOIN" && cmd != "332" && cmd != "366" && cmd != "353"
			 && cmd != "PING")
			{
				std::cerr << "Join error" << std::endl;
				return (-1);
			}
		}
	} while (msg.find("353") == msg.npos);
	return (0);
}

int	recv_answer_register(int sock_fd)
{
	int							ret;
	std::string					msg;
	std::string					cmd;
	std::vector<std::string>	args;

	do
	{
		if ((ret = recv_entire_msg(sock_fd, msg)) <= 0)
		{
			if (ret == 0)
			{
				std::cerr << "Connection lost" << std::endl;
				return (-1);
			}
			if (ret == -1 && errno != EAGAIN)
			{
				perror("Register");
				return (-1);
			}
			errno = 0;
			std::cout << "No answer" << std::endl;
		}
		else
		{
			pars_msg(msg, cmd, args);
			std::cout << "Received : " << msg;
			if (cmd != "001" && cmd != "002" && cmd != "003" && cmd != "004"
			 && cmd != "PING")
			{
				std::cerr << "Register error" << std::endl;
				return (-1);
			}
		}
	} while (msg.find("004") == msg.npos);
	return (0);
}

int	send_connection_msg(int sock_fd, std::string msg, std::string step)
{
	msg += EOM;
	if (send_message_fd(sock_fd, msg.c_str()))
	{
		perror("Connection error");
		return (-1);
	}
	if (recv_answer(sock_fd, step))
		return (-1);
	return (0);
}

int	connect_to_server(int sock_fd, char *pass, char *chan)
{
	std::string	tmp;

	tmp = "PASS ";
	tmp += pass;
	if (send_connection_msg(sock_fd, tmp, "Pass"))
		return (-1);

	tmp = "NICK ";
	tmp += NICKNAME;
	if (send_connection_msg(sock_fd, tmp, "Nick"))
		return (-1);

	tmp = "USER ";
	tmp += NICKNAME;
	tmp += " 0 * :Un Bot Sympa";
	tmp += EOM;
	if (send_message_fd(sock_fd, tmp.c_str()) || recv_answer_register(sock_fd))
	{
		perror("Connection error");
		return (-1);
	}

	tmp = "JOIN ";
	tmp += chan;
	tmp += EOM;
	if (send_message_fd(sock_fd, tmp.c_str()))
	{
		perror("Connection error");
		return (-1);
	}
	return (recv_answer_join(sock_fd));
}
