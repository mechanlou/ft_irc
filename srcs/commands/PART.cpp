#include "commands/PART.hpp"

part::part()
{
}

part::~part()
{
}

void	part::execute(std::string buf, Client *cli, std::vector<Channel> *chan, std::vector<pollfd> &fds)
{
    std::string msg;
	_getcmd(buf);

	if (_cmd.size() < 2)
	{
		err_needmoreparams(cli,fds,_cmd[0]);
		return;
	}
	Channel *tmp_chan = _check_chan(_cmd[1], chan);
	if (tmp_chan != NULL && !_check_client(cli, tmp_chan))
	{
		err_notochannel(cli,fds,_cmd[1]);
		return;
	}
	if (tmp_chan != NULL)
	{
		msg = ":" + cli->get_nickname() + "!" + cli->get_truename() + cli->get_ip() + " PART " + _cmd[1] + ":" + "bye" + END_OF_MSG;
		std::vector<Client *> members = tmp_chan->get_all_users();
		for (std::vector<Client *>::iterator it = members.begin(); it != members.end(); it++)
		{
			Client *c = *it;
			send(c->get_sock_fd(), msg.c_str(), msg.length(), 0);
		}
		tmp_chan->remove_user(cli);
		if(tmp_chan->get_all_users().size() == 0)
		{
			for(std::vector<Channel>::iterator it2 = chan->begin(); it2 != chan->end(); it2++)
			{	
				if((*it2).get_name() == tmp_chan->get_name())
				{
					chan->erase(it2);
					break;
				}
			}
		}
	}
	else
	{
		err_nosuchchannel(cli,fds,_cmd[1]);
		return;
	}
}