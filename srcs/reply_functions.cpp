#include "ircserver.hpp"

void	add_crlf(std::string &msg)
{
	msg.push_back('\r');
	msg.push_back('\n');
}

std::string	get_reply_prefix(void) // pas utilisée
{
	std::string	msg(":"); // starts with ':'
	msg += SERVER_NAME; // prefix (server name)
	msg.push_back(' ');
	return (msg);
}

int	err_nosuchnick(int fd, std::string nick)
{
	std::string	msg(ERR_NOSUCHNICK); // start with reply code

	msg.push_back(' ');
	msg += nick; // destination nickname
	msg.push_back(' ');
	msg += nick; //reply message
	msg += " :No such nick/channel";
	add_crlf(msg); //CRLF
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nosuchserver(int fd, std::string nick, std::string server)
{
	std::string	msg(ERR_NOSUCHSERVER);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += server;
	msg += " :No such server";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nosuchchannel(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_NOSUCHCHANNEL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :No such channel";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_cannotsendtochan(int fd, std::string nick, std::string chan)
{
	std::string	msg(ERR_CANNOTSENDTOCHAN);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += chan;
	msg += " :Cannot send to channel";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_toomanychannels(int fd, std::string nick, std::string chan)
{
	std::string	msg(ERR_TOOMANYCHANNELS);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += chan;
	msg += " :You have joined too many channels";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_wasnosuchnick(int fd, std::string nick)
{
	std::string	msg(ERR_WASNOSUCHNICK);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += nick;
	msg += " :There was no such nickname";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_toomanytargets(int fd, std::string nick, std::string target, std::string error_code, std::string abort_msg)
{
	std::string	msg(ERR_TOOMANYTARGETS);

	msg.push_back(' ');
	msg += nick;
	msg += " :";
	msg.append(error_code);
	msg += " recipients. ";
	msg.append(abort_msg);
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_noorigin(int fd, std::string nick)
{
	std::string	msg(ERR_NOORIGIN);

	msg.push_back(' ');
	msg += nick;
	msg += " :No origin specified";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_norecipient(int fd, std::string nick, std::string command)
{
	std::string	msg(ERR_NORECIPIENT);

	msg.push_back(' ');
	msg += nick;
	msg += " :No recipient given (";
	msg += command;
	msg.push_back(')');
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_notexttosend(int fd, std::string nick)
{
	std::string	msg(ERR_NOTEXTTOSEND);

	msg.push_back(' ');
	msg += nick;
	msg += " :No text to send";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_notoplevel(int fd, std::string nick, std::string mask)
{
	std::string	msg(ERR_NOTOPLEVEL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += mask;
	msg += " :No toplevel domain specified";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_wildtoplevel(int fd, std::string nick, std::string mask)
{
	std::string	msg(ERR_WILDTOPLEVEL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += mask;
	msg += " :Wildcard in top level domain";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_badmask(int fd, std::string nick, std::string mask)
{
	std::string	msg(ERR_BADMASK);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += mask;
	msg += " :Bad Server/host mask";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_unknowncommand(int fd, std::string nick, std::string command)
{
	std::string	msg(ERR_UNKNOWNCOMMAND);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += command;
	msg += " :Unknown command";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nomotd(int fd, std::string nick)
{
	std::string	msg(ERR_NOMOTD);

	msg.push_back(' ');
	msg += nick;
	msg += " :MOTD File is missing";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_noadmininfo(int fd, std::string nick, std::string server)
{
	std::string	msg(ERR_NOADMININFO);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += server;
	msg += " :No administrative info available";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_fileerror(int fd, std::string nick, std::string file_op, std::string file)
{
	std::string	msg(ERR_FILEERROR);

	msg.push_back(' ');
	msg += nick;
	msg += " :File error doing ";
	msg += file_op;
	msg += " on ";
	msg += file;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nonicknamegiven(int fd, std::string nick)
{
	std::string	msg(ERR_NONICKNAMEGIVEN);

	msg.push_back(' ');
	msg += nick;
	msg += " :No nickname given";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_erroneusnickname(int fd, std::string nick)
{
	std::string	msg(ERR_ERRONEUSNICKNAME);

	msg.push_back(' ');
	msg += nick;
	msg += " :Erroneous nickname";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nicknameinuse(int fd, std::string nick)
{
	std::string	msg(ERR_NICKNAMEINUSE);

	msg.push_back(' ');
	msg += nick;
	msg += " :Nickname already in use";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nickcollision(int fd, std::string nick, std::string user, std::string host)
{
	std::string	msg(ERR_NICKCOLLISION);

	msg.push_back(' ');
	msg += nick;
	msg += " :Nickname collision KILL from ";
	msg += user;
	msg.push_back('@');
	msg += host;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_unavailableresource(int fd, std::string nick, std::string resource)
{
	std::string	msg(ERR_UNAVAILABLERESOURCE);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += resource;
	msg += " :Nick/channel is temporarily unavailable";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_usernotinchannel(int fd, std::string nick, std::string target_nick, std::string channel)
{
	std::string	msg(ERR_USERNOTINCHANNEL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += target_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :They aren't on that channel";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_notochannel(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_NOTOCHANNEL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :You're not on that channel";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_useronchannel(int fd, std::string nick, std::string user, std::string channel)
{
	std::string	msg(ERR_USERONCHANNEL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += channel;
	msg += " :is already on channel";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nologin(int fd, std::string nick, std::string user)
{
	std::string	msg(ERR_NOLOGIN);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += user;
	msg += " :User not logged in";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_summondisabled(int fd, std::string nick)
{
	std::string	msg(ERR_SUMMONDISABLED);

	msg.push_back(' ');
	msg += nick;
	msg += " :SUMMON has been disabled";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_userdisabled(int fd, std::string nick)
{
	std::string	msg(ERR_USERSDISABLED);

	msg.push_back(' ');
	msg += nick;
	msg += " :USERS has been disabled";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_notregistered(int fd)
{
	std::string	msg(ERR_NOTREGISTERED);

	msg += " :You have not registered";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_needmoreparams(int fd, std::string nick, std::string command)
{
	std::string	msg(ERR_NEEDMOREPARAMS);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += command;
	msg += " :Not enough parameters";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_alreadyregistered(int fd, std::string nick)
{
	std::string	msg(ERR_ALREADYREGISTERED);

	msg.push_back(' ');
	msg += nick;
	msg += " :Unauthorized command (already registered)";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nopermforhost(int fd, std::string nick)
{
	std::string	msg(ERR_NOPERMFORHOST);

	msg.push_back(' ');
	msg += nick;
	msg += " :Your host isn't among the privileged";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_passwdmismatch(int fd)
{
	std::string	msg(ERR_PASSWDMISMATCH);

	msg += " :Password incorrect";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_yourebannedcreep(int fd, std::string nick)
{
	std::string	msg(ERR_YOUREBANNEDCREEP);

	msg.push_back(' ');
	msg += nick;
	msg += " :You are banned from this server";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_youwillbebanned(int fd, std::string nick)
{
	std::string	msg(ERR_YOUWILLBEBANNED);

	msg.push_back(' ');
	msg += nick;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_keyset(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_KEYSET);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Channel key already set";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_channelisfull(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_CHANNELISFULL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+l)";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_unknownmode(int fd, std::string nick, char mode, std::string channel)
{
	std::string	msg(ERR_UNKNOWNMODE);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg.push_back(mode);
	msg += " :is unknown mode char to me for ";
	msg += channel;
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_inviteonlychan(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_INVITEONLYCHAN);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+i)";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_bannedfromchan(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_BANNEDFROMCHAN);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+b)";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_badchannelkey(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_BADCHANNELKEY);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+k)";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_badchanmask(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_BADCHANMASK);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Bad Channel Mask";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nochanmodes(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_NOCHANMODES);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :Channel doesn't support modes";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_banlistfull(int fd, std::string nick, char stuff, std::string channel)
{
	std::string	msg(ERR_BANLISTFULL);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg.push_back(stuff);
	msg += " :Channel list is full";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_noprivileges(int fd, std::string nick)
{
	std::string	msg(ERR_NOPRIVILEGES);

	msg.push_back(' ');
	msg += nick;
	msg += " :Permission Denied- You're not an IRC operator";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_chanoprivsneeded(int fd, std::string nick, std::string channel)
{
	std::string	msg(ERR_CHANOPRIVSNEEDED);

	msg.push_back(' ');
	msg += nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :You're not channel operator";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_cantkillserver(int fd, std::string nick)
{
	std::string	msg(ERR_CANTKILLSERVER);

	msg.push_back(' ');
	msg += nick;
	msg += " :You can't kill a server";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_restricted(int fd, std::string nick)
{
	std::string	msg(ERR_RESTRICTED);

	msg.push_back(' ');
	msg += nick;
	msg += " :Your connection is restricted!";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_uniqoprivsneeded(int fd, std::string nick)
{
	std::string	msg(ERR_UNIQOPRIVSNEEDED);

	msg.push_back(' ');
	msg += nick;
	msg += " :You're not the original channel operator";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_nooperhost(int fd, std::string nick)
{
	std::string	msg(ERR_NOOPERHOST);

	msg.push_back(' ');
	msg += nick;
	msg += " :No O-lines for your host";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_umodeunknownflag(int fd, std::string nick)
{
	std::string	msg(ERR_UMODEUNKNOWNFLAG);

	msg.push_back(' ');
	msg += nick;
	msg += " :Unknown MODE flag";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}

int	err_usersdontmatch(int fd, std::string nick)
{
	std::string	msg(ERR_USERSDONTMATCH);

	msg.push_back(' ');
	msg += nick;
	msg += " :Cannot change mode for other users";
	add_crlf(msg);
	return (send_message_fd(fd, msg.c_str()));
}
