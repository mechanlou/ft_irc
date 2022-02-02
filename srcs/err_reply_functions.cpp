#include "ircserver.hpp"

void	add_crlf(std::string &msg)
{
	msg.push_back('\r');
	msg.push_back('\n');
}

std::string	get_reply_prefix(void) // pas utilisée
{
	std::string	msg(":"); // starts with ':'
	msg += SERV_NAME; // prefix (server name)
	msg.push_back(' ');
	return (msg);
}

void	err_nosuchnick(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOSUCHNICK); // start with reply code

	msg.push_back(' ');
	msg += dst.get_nickname(); // destination nickname
	msg.push_back(' ');
	msg += dst.get_nickname(); //reply message
	msg += " :No such nick/channel";
	add_crlf(msg); //CRLF
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nosuchserver(Client &dst, std::vector<pollfd> &fds, std::string server)
{
	std::string	msg(ERR_NOSUCHSERVER);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += server;
	msg += " :No such server";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nosuchchannel(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_NOSUCHCHANNEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :No such channel";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_cannotsendtochan(Client &dst, std::vector<pollfd> &fds, std::string chan)
{
	std::string	msg(ERR_CANNOTSENDTOCHAN);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += chan;
	msg += " :Cannot send to channel";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_toomanychannels(Client &dst, std::vector<pollfd> &fds, std::string chan)
{
	std::string	msg(ERR_TOOMANYCHANNELS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += chan;
	msg += " :You have joined too many channels";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_wasnosuchnick(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_WASNOSUCHNICK);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :There was no such nickname";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_toomanytargets(Client &dst, std::vector<pollfd> &fds, std::string target, std::string error_code, std::string abort_msg)
{
	std::string	msg(ERR_TOOMANYTARGETS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :";
	msg.append(error_code);
	msg += " recipients. ";
	msg.append(abort_msg);
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_noorigin(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOORIGIN);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :No origin specified";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_norecipient(Client &dst, std::vector<pollfd> &fds, std::string command)
{
	std::string	msg(ERR_NORECIPIENT);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :No recipient given (";
	msg += command;
	msg.push_back(')');
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_notexttosend(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOTEXTTOSEND);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :No text to send";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_notoplevel(Client &dst, std::vector<pollfd> &fds, std::string mask)
{
	std::string	msg(ERR_NOTOPLEVEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += mask;
	msg += " :No toplevel domain specified";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_wildtoplevel(Client &dst, std::vector<pollfd> &fds, std::string mask)
{
	std::string	msg(ERR_WILDTOPLEVEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += mask;
	msg += " :Wildcard in top level domain";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_badmask(Client &dst, std::vector<pollfd> &fds, std::string mask)
{
	std::string	msg(ERR_BADMASK);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += mask;
	msg += " :Bad Server/host mask";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_unknowncommand(Client &dst, std::vector<pollfd> &fds, std::string command)
{
	std::string	msg(ERR_UNKNOWNCOMMAND);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += command;
	msg += " :Unknown command";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nomotd(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOMOTD);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :MOTD File is missing";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_noadmininfo(Client &dst, std::vector<pollfd> &fds, std::string server)
{
	std::string	msg(ERR_NOADMININFO);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += server;
	msg += " :No administrative info available";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_fileerror(Client &dst, std::vector<pollfd> &fds, std::string file_op, std::string file)
{
	std::string	msg(ERR_FILEERROR);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :File error doing ";
	msg += file_op;
	msg += " on ";
	msg += file;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nonicknamegiven(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NONICKNAMEGIVEN);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :No nickname given";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_erroneusnickname(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_ERRONEUSNICKNAME);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Erroneous nickname";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nicknameinuse(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NICKNAMEINUSE);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Nickname already in use";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nickcollision(Client &dst, std::vector<pollfd> &fds, std::string user, std::string host)
{
	std::string	msg(ERR_NICKCOLLISION);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Nickname collision KILL from ";
	msg += user;
	msg.push_back('@');
	msg += host;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_unavailableresource(Client &dst, std::vector<pollfd> &fds, std::string resource)
{
	std::string	msg(ERR_UNAVAILABLERESOURCE);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += resource;
	msg += " :Nick/channel is temporarily unavailable";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_usernotinchannel(Client &dst, std::vector<pollfd> &fds, std::string target_nick, std::string channel)
{
	std::string	msg(ERR_USERNOTINCHANNEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += target_nick;
	msg.push_back(' ');
	msg += channel;
	msg += " :They aren't on that channel";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_notochannel(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_NOTOCHANNEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :You're not on that channel";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_useronchannel(Client &dst, std::vector<pollfd> &fds, std::string user, std::string channel)
{
	std::string	msg(ERR_USERONCHANNEL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += user;
	msg.push_back(' ');
	msg += channel;
	msg += " :is already on channel";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nologin(Client &dst, std::vector<pollfd> &fds, std::string user)
{
	std::string	msg(ERR_NOLOGIN);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += user;
	msg += " :User not logged in";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_summondisabled(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_SUMMONDISABLED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :SUMMON has been disabled";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_userdisabled(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_USERSDISABLED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :USERS has been disabled";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_notregistered(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOTREGISTERED);

	msg += " :You have not registered";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_needmoreparams(Client &dst, std::vector<pollfd> &fds, std::string command)
{
	std::string	msg(ERR_NEEDMOREPARAMS);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += command;
	msg += " :Not enough parameters";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_alreadyregistered(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_ALREADYREGISTERED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Unauthorized command (already registered)";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nopermforhost(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOPERMFORHOST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Your host isn't among the privileged";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_passwdmismatch(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_PASSWDMISMATCH);

	msg += " :Password incorrect";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_yourebannedcreep(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_YOUREBANNEDCREEP);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :You are banned from this server";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_youwillbebanned(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_YOUWILLBEBANNED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_keyset(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_KEYSET);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Channel key already set";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_channelisfull(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_CHANNELISFULL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+l)";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_unknownmode(Client &dst, std::vector<pollfd> &fds, char mode, std::string channel)
{
	std::string	msg(ERR_UNKNOWNMODE);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg.push_back(mode);
	msg += " :is unknown mode char to me for ";
	msg += channel;
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_inviteonlychan(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_INVITEONLYCHAN);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+i)";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_bannedfromchan(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_BANNEDFROMCHAN);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+b)";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_badchannelkey(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_BADCHANNELKEY);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Cannot join channel (+k)";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_badchanmask(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_BADCHANMASK);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Bad Channel Mask";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nochanmodes(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_NOCHANMODES);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :Channel doesn't support modes";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_banlistfull(Client &dst, std::vector<pollfd> &fds, char stuff, std::string channel)
{
	std::string	msg(ERR_BANLISTFULL);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg.push_back(' ');
	msg.push_back(stuff);
	msg += " :Channel list is full";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_noprivileges(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOPRIVILEGES);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Permission Denied- You're not an IRC operator";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_chanoprivsneeded(Client &dst, std::vector<pollfd> &fds, std::string channel)
{
	std::string	msg(ERR_CHANOPRIVSNEEDED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg.push_back(' ');
	msg += channel;
	msg += " :You're not channel operator";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_cantkillserver(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_CANTKILLSERVER);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :You can't kill a server";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_restricted(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_RESTRICTED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Your connection is restricted!";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_uniqoprivsneeded(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_UNIQOPRIVSNEEDED);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :You're not the original channel operator";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_nooperhost(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_NOOPERHOST);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :No O-lines for your host";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_umodeunknownflag(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_UMODEUNKNOWNFLAG);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Unknown MODE flag";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}

void	err_usersdontmatch(Client &dst, std::vector<pollfd> &fds)
{
	std::string	msg(ERR_USERSDONTMATCH);

	msg.push_back(' ');
	msg += dst.get_nickname();
	msg += " :Cannot change mode for other users";
	add_crlf(msg);
	send_msg_client(dst, fds, msg.c_str());
}
