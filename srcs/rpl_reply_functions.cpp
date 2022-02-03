#include "ircserver.hpp"


void	rpl_welcome(Client &dst, std::vector<pollfd> &fds, std::string user, std::string host)
{
	std::string	msg(RPL_WELCOME);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " Welcome to the Internet Relay Network ";
	msg += dst.get_nickname();
	msg.push_back('!');
	msg += user;
	msg.push_back('@');
	msg += host;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_yourhost(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_YOURHOST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += "Your host is ";
	msg += SERV_NAME;
	msg += ", running version ";
	msg += VERSION;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_created(Client &dst, std::vector<pollfd> &fds) // fait un truc un peu mieux quand meme
{
	std::string	msg(RPL_CREATED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += "This server was created ";
	msg += START_DATE;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_myinfo(Client &dst, std::vector<pollfd> &fds, std::string user_modes, std::string channel_modes)
{
	std::string	msg(RPL_MYINFO);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += SERV_NAME;
	msg.push_back(' ');
	msg += VERSION;
	msg.push_back(' ');
	msg += user_modes;
	msg.push_back(' ');
	msg += channel_modes;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_pong(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg("PONG");

	msg.push_back(' ');
	msg += SERV_NAME;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

// void	rpl_bounce(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }


// void	rpl_none(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

void	rpl_userhost(Client &dst, std::vector<pollfd> &fds, std::string *replies, int nb_replies)
{
	std::string	msg(RPL_USERHOST);
	int	i;

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :";
	i = 0;
	while (i < nb_replies)
	{
		if (i > 0)
			msg.push_back(' ');
		msg += replies[i];
		i++;
	}
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_ison(Client &dst, std::vector<pollfd> &fds, std::string *nicks, int nb_nicks)
{
	std::string	msg(RPL_ISON);
	int	i;

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :";
	i = 0;
	while (i < nb_nicks)
	{
		if (i > 0)
			msg.push_back(' ');
		msg += nicks[i];
		i++;
	}
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_away(Client &dst, std::vector<pollfd> &fds, std::string away_nick, std::string away_msg)
{
	std::string	msg(RPL_AWAY);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += away_nick;
	msg += " :";
	msg += away_msg;	
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_unaway(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_UNAWAY);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :You are no longer marked as being away";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_nowaway(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_NOWAWAY);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :You have been marked as being away";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whoisuser(Client &dst, std::vector<pollfd> &fds, std::string nick, std::string user, std::string host, std::string real_name)
{
	std::string	msg(RPL_WHOISUSER);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += host;
	msg += " * :";
	msg += real_name;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whoisserver(Client &dst, std::vector<pollfd> &fds, std::string nick, std::string server, std::string serv_info)
{
	std::string	msg(RPL_WHOISSERVER);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += server;
	msg += " :";
	msg += serv_info;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whoisoperator(Client &dst, std::vector<pollfd> &fds, std::string nick)
{
	std::string	msg(RPL_WHOISOPERATOR);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg += " :is an IRC operator";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whoisidle(Client &dst, std::vector<pollfd> &fds, std::string nick, int len)
{
	std::string			msg(RPL_WHOISIDLE);
	std::ostringstream	stream;

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	stream << len;
	msg += stream.str();
	msg += " :seconds idle";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofwhois(Client &dst, std::vector<pollfd> &fds, std::string nick)
{
	std::string	msg(RPL_ENDOFWHOIS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg += " :End of WHOIS list";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whoischannels(Client &dst, std::vector<pollfd> &fds, std::string nick, std::string *channels, int nb_channels)
{
	std::string	msg(RPL_WHOISCHANNELS);
	int	i;

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg += " :";
	i = 0;
	while (i < nb_channels)
	{
		msg += channels[i];
		msg.push_back(' ');
		i++;
	}
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whowasuser(Client &dst, std::vector<pollfd> &fds, std::string nick, std::string user, std::string host, std::string real_name)
{
	std::string	msg(RPL_WHOWASUSER);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += host;
	msg += " * :";
	msg += real_name;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofwhowas(Client &dst, std::vector<pollfd> &fds, std::string nick)
{
	std::string	msg(RPL_ENDOFWHOWAS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += nick;
	msg += " :End of WHOWAS";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_liststart(Client &dst, std::vector<pollfd> &fds)
{
 	std::string	msg(RPL_LISTSTART);

 	msg.push_back(' ');
	msg += "Channel :Users Name";
 	add_crlf(msg);
 	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_list(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(RPL_LIST);

	msg.push_back(' ');
	msg += channel;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_listend(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_LISTEND);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += ":End of /LIST";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_channelmodeis(Client &dst, std::vector<pollfd> &fds, std::string channel, std::string mode, std::string mode_params)
{
	std::string	msg(RPL_CHANNELMODEIS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += mode;
	msg.push_back(' ');
	msg += mode_params;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_notopic(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(RPL_NOTOPIC);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :No topic is set";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_topic(Client &dst, std::vector<pollfd> &fds, std::string channel, std::string topic)
{
	std::string	msg(RPL_TOPIC);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :";
	msg += topic;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_inviting(Client &dst, std::vector<pollfd> &fds, std::string channel, std::string nick)
{
	std::string	msg(RPL_INVITING);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += nick;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_summoning(Client &dst, std::vector<pollfd> &fds, std::string user)
{
	std::string	msg(RPL_SUMMONING);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += user;
	msg += " :Summoning user to IRC";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_exceptlist(Client &dst, std::vector<pollfd> &fds, std::string channel, std::string mask)
{
	std::string	msg(RPL_EXCEPTLIST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += mask;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofexceptlist(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(RPL_ENDOFEXCEPTLIST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :End of channel exception list";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_version(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_VERSION);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += VERSION;
	msg.push_back('.');
	msg += "normal";
	msg.push_back (' ');
	msg += SERV_NAME;
	msg += " :";
	msg += "Watch JoJo";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_whoreply(Client &dst, std::vector<pollfd> &fds, std::string chan, std::string user, std::string host, std::string server, std::string nick, std::string weird_args, int hop_count, std::string real_name)
{
	std::string			msg(RPL_WHOREPLY);
	std::ostringstream	itoa;

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += chan;
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += host;
	msg.push_back(' ');
	msg += server;
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += weird_args;
	msg += " :";
	itoa << hop_count;
	msg += itoa.str();
	msg.push_back(' ');
	msg += real_name;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofwho(Client &dst, std::vector<pollfd> &fds, std::string name)
{
	std::string	msg(RPL_ENDOFWHO);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += name;
	msg += " :End of WHO list";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

 void	rpl_namreply(Client *dst, std::vector<pollfd> &fds, Channel *chan) // AREVOIR
 {
 	
	 std::string	msg(RPL_NAMREPLY);
 	std::vector<Client *>::iterator it = chan->get_all_users().begin();
 	std::vector<Client *>::iterator it_end = chan->get_all_users().end();
 	std::vector<Client *>::iterator it_op = chan->get_operators().begin();
 	std::vector<Client *>::iterator it_op_end = chan->get_operators().end();

 	msg.push_back(' ');
 	msg += dst->get_nickname();
 	msg.push_back(' ');
 	msg += chan->get_name();
 	msg += " :";
 	while (it != it_end)
 	{
 		if (std::find(it_op, it_op_end, *it) != it_op_end)
 			msg.push_back('@');
 		msg += (*it)->get_nickname();
		it++;
 		if (it != it_end)
 			msg.push_back(' ');
 	}
 	add_crlf(msg);
 	send_msg_client(*dst, fds, msg.c_str());
 }

void	rpl_endofnames(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(RPL_ENDOFNAMES);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :End of NAMES list";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_links(Client &dst, std::vector<pollfd> &fds, std::string mask, std::string server, int hop_count, std::string serv_info)
{
	std::string			msg(RPL_LINKS);
	std::ostringstream	itoa;

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += mask;
	msg.push_back(' ');
	msg += server;
	msg += " :";
	itoa << hop_count;
	msg += itoa.str();
	msg.push_back(' ');
	msg += serv_info;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endoflinks(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_ENDOFLINKS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += "";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_banlist(Client &dst, std::vector<pollfd> &fds, std::string channel, std::string banmask)
{
	std::string	msg(RPL_BANLIST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += banmask;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofbanlist(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(RPL_ENDOFBANLIST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :End of channel ban list";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_info(Client &dst, std::vector<pollfd> &fds, std::string info)
{
	std::string	msg(RPL_INFO);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :";
	msg += info;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofinfo(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOTOPLEVEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :End of INFO list";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_motdstart(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_MOTDSTART);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :- ";
	msg += SERV_NAME;
	msg += "Message of the day - ";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_motd(Client &dst, std::vector<pollfd> &fds, std::string msg)
{
	std::string	msg(RPL_MOTD);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :- ";
	msg += msg;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofmotd(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_ENDOFMOTD);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :End of the MOTD command";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_youreoper(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_YOUREOPER);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :You are now an IRC operator";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_rehashing(Client &dst, std::vector<pollfd> &fds, std::string config_file)
{
	std::string	msg(RPL_REHASHING);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += config_file;
	msg += " :Rehashing";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_time(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_TIME);
	time_t		now;
	char		*date_time;

	now = time(0);
	date_time = ctime(&now);
	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += SERV_NAME;
	msg += " :";
	msg +=date_time;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_usersstart(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_USERSSTART);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :UsersID Terminal Host";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_users(Client &dst, std::vector<pollfd> &fds, std::string username, std::string ttyline, std::string hostname)
{
	std::string	msg(RPL_USERS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :";
	msg += username;
	msg.push_back(' ');
	msg += ttyline;
	msg.push_back(' ');
	msg += hostname;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_endofusers(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_ENDOFUSERS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :End of users";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	rpl_nousers(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(RPL_NOUSERS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Nobody logged in";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

// void	rpl_tracelink(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(RPL_TRACELINK);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_traceconnecting(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_tracehandshake(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_traceunknown(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_traceoperator(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_traceuser(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_traceserver(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_tracenewtype(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_tracelog(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statslinkinfo(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(RPL_STATSLINKINFO);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statscommands(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statscline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statsnline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statsiline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statskline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statsyline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_endofstats(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statslline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statsuptime(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statsoline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_statshline(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

void	rpl_umodeis(Client &dst, std::vector<pollfd> &fds, std::string user_mode)
{
	std::string	msg(RPL_UMODEIS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += user_mode;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

// void	rpl_luserclient(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(RPL_LUSERCLIENT);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_luserop(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_luserunknown(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_luserchannels(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_luserme(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_adminme(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_adminloc1(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_adminloc2(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }

// void	rpl_adminemail(Client &dst, std::vector<pollfd> &fds)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dst.get_nickname();
// 	msg += "";
// 	add_crlf(msg);
// 	send_msg_client(dst, fds, msg.c_str());
// }
