#include "commands/PRIVMSG.hpp"

privmsg::privmsg(void) {}

privmsg::~privmsg(void) {}

void	privmsg::_send_channel(std::string msg, Client *src,
	std::vector<Channel> *all_chans,
	std::vector<pollfd> &fds, std::vector<std::string> args)
{
	std::vector<Channel>::iterator	it_chan;
	std::vector<Channel>::iterator	it_chan_end;

	it_chan = all_chans->begin();
	it_chan_end = all_chans->end();
	// int i = 0;
	while (it_chan != it_chan_end)
	{
		// std::cout << "nb : " << i++ << " name : \"" << it_chan->get_name() << "\"" << std::endl;
		if (it_chan->get_name() == args[0])
		{
			if (it_chan->is_members(src->get_nickname()))
				it_chan->msg_to_channel_no_me(msg.c_str(), fds, src);
			else
				err_cannotsendtochan(*src, fds, it_chan->get_name());
			break;
		}
		it_chan++;
	}
	if (it_chan == it_chan_end)
		err_nosuchnick(*src, fds);
}

void	privmsg::_send_client(std::string msg, Client *src,
	std::vector<Client> *all_clients, std::vector<pollfd> &fds,
	std::vector<std::string> args)
{
	std::vector<Client>::iterator	it_cli;
	std::vector<Client>::iterator	it_cli_end;

	it_cli = all_clients->begin();
	it_cli_end = all_clients->end();
	while (it_cli != it_cli_end)
	{
		if (it_cli->get_nickname() == args[0])
		{
			send_msg_client(*it_cli, fds, msg.c_str());
			break;
		}
		it_cli++;
	}
	if (it_cli == it_cli_end)
		err_nosuchnick(*src, fds);
}

void	privmsg::execute(std::string msg, Client *src, std::vector<Channel> *all_chans,
	std::vector<Client> *all_clients, std::vector<pollfd> &fds)
{
	std::string					cmd;
	std::vector<std::string>	args;

	pars_msg(msg, cmd, args);
	if (msg[0] != ':')
		msg.insert(0, src->get_full_prefix());
	if (args.size() == 0)
	{
		err_norecipient(*src, fds, "PRIVMSG");
		return ;
	}
	if (args.size() == 1)
	{
		err_notexttosend(*src, fds);
		return ;
	}
	if (args[0][0] == '#')
		_send_channel(msg, src, all_chans, fds, args);
	else
		_send_client(msg, src, all_clients, fds, args);
}