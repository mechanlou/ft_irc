#include "ircserver.hpp"


int	rpl_welcome(int fd, std::string dest_nick, std::string user, std::string host)
{
	std::string	msg(RPL_WELCOME);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " Welcome to the Internet Relay Network ";
	msg += dest_nick;
	msg.push_back('!');
	msg += user;
	msg.push_back('@');
	msg += host;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_yourhost(int fd, std::string dest_nick)
{
	std::string	msg(RPL_YOURHOST);

	msg.push_back(' ');
	msg += dest_nick;
	msg += "Your host is ";
	msg += SERV_NAME;
	msg += ", running version ";
	msg += VERSION;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_created(int fd, std::string dest_nick) // fait un truc un peu mieux quand meme
{
	std::string	msg(RPL_CREATED);

	msg.push_back(' ');
	msg += dest_nick;
	msg += "This server was created ";
	msg += START_DATE;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_myinfo(int fd, std::string dest_nick, std::string user_modes, std::string channel_modes)
{
	std::string	msg(RPL_MYINFO);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += SERV_NAME;
	msg.push_back(' ');
	msg += VERSION;
	msg.push_back(' ');
	msg += user_modes;
	msg.push_back(' ');
	msg += channel_modes;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_pong(int fd)
{
	std::string	msg("PONG");

	msg.push_back(' ');
	msg += SERV_NAME;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

// int	rpl_bounce(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }


// int	rpl_none(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

int	rpl_userhost(int fd, std::string dest_nick, std::string *replies, int nb_replies)
{
	std::string	msg(RPL_USERHOST);
	int	i;

	msg.push_back(' ');
	msg += dest_nick;
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
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_ison(int fd, std::string dest_nick, std::string *nicks, int nb_nicks)
{
	std::string	msg(RPL_ISON);
	int	i;

	msg.push_back(' ');
	msg += dest_nick;
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
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_away(int fd, std::string dest_nick, std::string away_nick, std::string away_msg)
{
	std::string	msg(RPL_AWAY);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += away_nick;
	msg += " :";
	msg += away_msg;	
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_unaway(int fd, std::string dest_nick)
{
	std::string	msg(RPL_UNAWAY);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :You are no longer marked as being away";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_nowaway(int fd, std::string dest_nick)
{
	std::string	msg(RPL_NOWAWAY);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :You have been marked as being away";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whoisuser(int fd, std::string dest_nick, std::string nick, std::string user, std::string host, std::string real_name)
{
	std::string	msg(RPL_WHOISUSER);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += host;
	msg += " * :";
	msg += real_name;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whoisserver(int fd, std::string dest_nick, std::string nick, std::string server, std::string serv_info)
{
	std::string	msg(RPL_WHOISSERVER);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += server;
	msg += " :";
	msg += serv_info;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whoisoperator(int fd, std::string dest_nick, std::string nick)
{
	std::string	msg(RPL_WHOISOPERATOR);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg += " :is an IRC operator";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whoisidle(int fd, std::string dest_nick, std::string nick, int len)
{
	std::string			msg(RPL_WHOISIDLE);
	std::ostringstream	stream;

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	stream << len;
	msg += stream.str();
	msg += " :seconds idle";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofwhois(int fd, std::string dest_nick, std::string nick)
{
	std::string	msg(RPL_ENDOFWHOIS);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg += " :End of WHOIS list";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whoischannels(int fd, std::string dest_nick, std::string nick,
	std::string *channels, int nb_channels)
{
	std::string	msg(RPL_WHOISCHANNELS);
	int	i;

	msg.push_back(' ');
	msg += dest_nick;
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
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whowasuser(int fd, std::string dest_nick, std::string nick,
	std::string user, std::string host, std::string real_name)
{
	std::string	msg(RPL_WHOWASUSER);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += host;
	msg += " * :";
	msg += real_name;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofwhowas(int fd, std::string dest_nick, std::string nick)
{
	std::string	msg(RPL_ENDOFWHOWAS);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += nick;
	msg += " :End of WHOWAS";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_liststart(int fd)
{
 	std::string	msg(RPL_LISTSTART);

 	msg.push_back(' ');
	msg += "Channel :Users Name";
 	add_crlf(msg);
 	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_list(int fd, std::string channel)
{
	std::string	msg(RPL_LIST);

	msg.push_back(' ');
	msg += channel;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_listend(int fd, std::string dest_nick)
{
	std::string	msg(RPL_LISTEND);

	msg.push_back(' ');
	msg += dest_nick;
	msg += ":End of /LIST";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_channelmodeis(int fd, std::string dest_nick, std::string channel,
	std::string mode, std::string mode_params)
{
	std::string	msg(RPL_CHANNELMODEIS);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += mode;
	msg.push_back(' ');
	msg += mode_params;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_notopic(int fd, std::string dest_nick, std::string channel)
{
	std::string	msg(RPL_NOTOPIC);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :No topic is set";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_topic(int fd, std::string dest_nick, std::string channel, std::string topic)
{
	std::string	msg(RPL_TOPIC);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :";
	msg += topic;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_inviting(int fd, std::string dest_nick, std::string channel, std::string nick)
{
	std::string	msg(RPL_INVITING);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += nick;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_summoning(int fd, std::string dest_nick, std::string user)
{
	std::string	msg(RPL_SUMMONING);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += user;
	msg += " :Summoning user to IRC";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_exceptlist(int fd, std::string dest_nick, std::string channel,
	std::string mask)
{
	std::string	msg(RPL_EXCEPTLIST);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += mask;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofexceptlist(int fd, std::string dest_nick, std::string channel)
{
	std::string	msg(RPL_ENDOFEXCEPTLIST);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :End of channel exception list";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_version(int fd, std::string dest_nick)
{
	std::string	msg(RPL_VERSION);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += VERSION;
	msg.push_back('.');
	msg += "normal";
	msg.push_back (' ');
	msg += SERV_NAME;
	msg += " :";
	msg += "Watch JoJo";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_whoreply(int fd, std::string dest_nick, std::string chan,
	std::string user, std::string host, std::string server, std::string nick,
	std::string weird_args, int hop_count, std::string real_name)
{
	std::string			msg(RPL_WHOREPLY);
	std::ostringstream	itoa;

	msg.push_back(' ');
	msg += dest_nick;
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
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofwho(int fd, std::string dest_nick, std::string name)
{
	std::string	msg(RPL_ENDOFWHO);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += name;
	msg += " :End of WHO list";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

// int	rpl_namreply(int fd, std::string dest_nick, Channel chan) // AREVOIR
// {
// 	std::string	msg(RPL_NAMREPLY);
// 	std::vector<Client *>::iterator it = chan.get_chan_users().begin();
// 	std::vector<Client *>::iterator it_end = chan.get_chan_users().end();
// 	std::vector<Client *>::iterator it_op = chan.get_chan_operators().begin();
// 	std::vector<Client *>::iterator it_op_end = chan.get_chan_operators().end();

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg.push_back(' ');
// 	msg += chan.name;
// 	msg += " :";
// 	while (it != it_end)
// 	{
// 		if (std::find(it_op, it_op_end, *it) != it_op_end)
// 			msg.push_back('@');
// 		msg += (*it)->nickname;
// 		it++;
// 		if (it != it_end)
// 			msg.push_back(' ');
// 	}
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

int	rpl_endofnames(int fd, std::string dest_nick, std::string channel)
{
	std::string	msg(RPL_ENDOFNAMES);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :End of NAMES list";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_links(int fd, std::string dest_nick, std::string mask,
	std::string server, int hop_count, std::string serv_info)
{
	std::string			msg(RPL_LINKS);
	std::ostringstream	itoa;

	msg.push_back(' ');
	msg += dest_nick;
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
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endoflinks(int fd, std::string dest_nick)
{
	std::string	msg(RPL_ENDOFLINKS);

	msg.push_back(' ');
	msg += dest_nick;
	msg += "";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_banlist(int fd, std::string dest_nick, std::string channel, std::string banmask)
{
	std::string	msg(RPL_BANLIST);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg += banmask;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofbanlist(int fd, std::string dest_nick, std::string channel)
{
	std::string	msg(RPL_ENDOFBANLIST);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :End of channel ban list";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_info(int fd, std::string dest_nick, std::string info)
{
	std::string	msg(RPL_INFO);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :";
	msg += info;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofinfo(int fd, std::string dest_nick)
{
	std::string	msg(ERR_NOTOPLEVEL);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :End of INFO list";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_motdstart(int fd, std::string dest_nick)
{
	std::string	msg(RPL_MOTDSTART);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :- ";
	msg += SERV_NAME;
	msg += "Message of the day - ";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_motd(int fd, std::string dest_nick, std::string msg)
{
	std::string	msg(RPL_MOTD);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :- ";
	msg += msg;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofmotd(int fd, std::string dest_nick)
{
	std::string	msg(RPL_ENDOFMOTD);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :End of the MOTD command";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_youreoper(int fd, std::string dest_nick)
{
	std::string	msg(RPL_YOUREOPER);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :You are now an IRC operator";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_rehashing(int fd, std::string dest_nick, std::string config_file)
{
	std::string	msg(RPL_REHASHING);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += config_file;
	msg += " :Rehashing";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_time(int fd, std::string dest_nick)
{
	std::string	msg(RPL_TIME);
	time_t		now;
	char		*date_time;

	now = time(0);
	date_time = ctime(&now);
	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += SERV_NAME;
	msg += " :";
	msg +=date_time;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_usersstart(int fd, std::string dest_nick)
{
	std::string	msg(RPL_USERSSTART);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :UsersID Terminal Host";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_users(int fd, std::string dest_nick, std::string username,
	std::string ttyline, std::string hostname)
{
	std::string	msg(RPL_USERS);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :";
	msg += username;
	msg.push_back(' ');
	msg += ttyline;
	msg.push_back(' ');
	msg += hostname;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_endofusers(int fd, std::string dest_nick)
{
	std::string	msg(RPL_ENDOFUSERS);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :End of users";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	rpl_nousers(int fd, std::string dest_nick)
{
	std::string	msg(RPL_NOUSERS);

	msg.push_back(' ');
	msg += dest_nick;
	msg += " :Nobody logged in";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

// int	rpl_tracelink(int fd, std::string dest_nick)
// {
// 	std::string	msg(RPL_TRACELINK);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_traceconnecting(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_tracehandshake(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_traceunknown(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_traceoperator(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_traceuser(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_traceserver(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_tracenewtype(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_tracelog(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statslinkinfo(int fd, std::string dest_nick)
// {
// 	std::string	msg(RPL_STATSLINKINFO);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statscommands(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statscline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statsnline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statsiline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statskline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statsyline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_endofstats(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statslline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statsuptime(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statsoline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_statshline(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

int	rpl_umodeis(int fd, std::string dest_nick, std::string user_mode)
{
	std::string	msg(RPL_UMODEIS);

	msg.push_back(' ');
	msg += dest_nick;
	msg.push_back(' ');
	msg += user_mode;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

// int	rpl_luserclient(int fd, std::string dest_nick)
// {
// 	std::string	msg(RPL_LUSERCLIENT);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_luserop(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_luserunknown(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_luserchannels(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_luserme(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_adminme(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_adminloc1(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_adminloc2(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }

// int	rpl_adminemail(int fd, std::string dest_nick)
// {
// 	std::string	msg(ERR_NOTOPLEVEL);

// 	msg.push_back(' ');
// 	msg += dest_nick;
// 	msg += "";
// 	add_crlf(msg);
// 	return (send_message_fd(fd, msg.c_str()));
// }
