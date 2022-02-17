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
		msg = ":" + cli->get_nickname() + "!" + cli->get_truename() + cli->get_ip() + " PART " + _cmd[1] + " :" + "bye" + END_OF_MSG;
		tmp_chan->msg_to_channel(msg.c_str(), fds);
		tmp_chan->remove_user(cli);
		if(tmp_chan->get_operators().size() == 0 && tmp_chan->get_all_users().size() > 0)
		{
			tmp_chan->add_operator_user(*(tmp_chan->get_all_users().begin()));
		}
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