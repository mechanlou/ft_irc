#pragma once
#include "ircserver.hpp"

// errors

int	err_nosuchnick(int fd, std::string dest_nick);
int	err_nosuchserver(int fd, std::string server);
int	err_nosuchchannel(int fd, std::string channel);
int	err_cannotsendtochan(int fd, std::string chan);
int	err_toomanychannels(int fd, std::string chan);
int	err_wasnosuchnick(int fd, std::string dest_nick);
int	err_toomanytargets(int fd, std::string target, short error_code, std::string abort_msg);
int	err_nosuchservice(int fd, std::string service_name);
int	err_noorigin(int fd);
int	err_norecipient(int fd, std::string command);
int	err_notexttosend(int fd);
int	err_notoplevel(int fd, std::string mask);
int	err_wildtoplevel(int fd, std::string mask);
int	err_badmask(int fd, std::string mask);
int	err_unknowncommand(int fd, std::string command);
int	err_nomotd(int fd);
int	err_noadmininfo(int fd, std::string server);
int	err_fileerror(int fd, std::string file_op, std::string file);
int	err_nonicknamegiven(int fd);
int	err_erroneusnickname(int fd, std::string dest_nick);
int	err_nicknameinuse(int fd, std::string dest_nick);
int	err_nickcollision(int fd, std::string dest_nick, std::string user, std::string host);
int	err_unavailableresource(int fd, std::string resource);
int	err_usernotinchannel(int fd, std::string dest_nick, std::string channel);
int	err_notochannel(int fd, std::string channel);
int	err_useronchannel(int fd, std::string user, std::string channel);
int	err_nologin(int fd, std::string user);
int	err_summondisabled(int fd);
int	err_userdisabled(int fd);
int	err_notregistered(int fd);
int	err_needmoreparams(int fd, std::string command);
int	err_alreadyregistered(int fd);
int	err_nopermforhost(int fd);
int	err_passwdmismatch(int fd);
int	err_yourebannedcreep(int fd);
int	err_youwillbebanned(int fd);
int	err_keyset(int fd, std::string channel);
int	err_channelisfull(int fd, std::string channel);
int	err_unknownmode(int fd, char mode, std::string channel);
int	err_inviteonlychan(int fd, std::string channel);
int	err_bannedfromchan(int fd, std::string channel);
int	err_badchannelkey(int fd, std::string channel);
int	err_badchanmask(int fd, std::string channel);
int	err_nochanmodes(int fd, std::string channel);
int	err_banlistfull(int fd, char stuff, std::string channel);
int	err_noprivileges(int fd);
int	err_chanoprivsneeded(int fd, std::string channel);
int	err_cantkillserver(int fd);
int	err_restricted(int fd);
int	err_uniqoprivsneeded(int fd);
int	err_nooperhost(int fd);
int	err_umodeunknownflag(int fd);
int	err_usersdontmatch(int fd);

// messages

int	rpl_welcome(int fd, std::string dest_nick, std::string user, std::string host);
int	rpl_yourhost(int fd, std::string dest_nick);
int	rpl_created(int fd, std::string dest_nick); // fait un truc un peu mieux quand meme
int	rpl_myinfo(int fd, std::string dest_nick, std::string user_modes, std::string channel_modes);
int	rpl_pong(int fd);
// int	rpl_bounce(int fd, std::string dest_nick);
// int	rpl_none(int fd, std::string dest_nick);
int	rpl_userhost(int fd, std::string dest_nick, std::string *replies, int nb_replies);
int	rpl_ison(int fd, std::string dest_nick, std::string *nicks, int nb_nicks);
int	rpl_away(int fd, std::string dest_nick, std::string away_nick, std::string away_msg);
int	rpl_unaway(int fd, std::string dest_nick);
int	rpl_nowaway(int fd, std::string dest_nick);
int	rpl_whoisuser(int fd, std::string dest_nick, std::string nick, std::string user, std::string host, std::string real_name);
int	rpl_whoisserver(int fd, std::string dest_nick, std::string nick, std::string server, std::string serv_info);
int	rpl_whoisoperator(int fd, std::string dest_nick, std::string nick);
int	rpl_whoisidle(int fd, std::string dest_nick, std::string nick, int len);
int	rpl_endofwhois(int fd, std::string dest_nick, std::string nick);
int	rpl_whoischannels(int fd, std::string dest_nick, std::string nick,
	std::string *channels, int nb_channels);
int	rpl_whowasuser(int fd, std::string dest_nick, std::string nick,
	std::string user, std::string host, std::string real_name);
int	rpl_endofwhowas(int fd, std::string dest_nick, std::string nick);
// int	rpl_liststart(int fd, std::string dest_nick);
int	rpl_list(int fd, std::string dest_nick, std::string channel, std::string visible, std::string topic);
int	rpl_listend(int fd, std::string dest_nick);
int	rpl_channelmodeis(int fd, std::string dest_nick, std::string channel,
	std::string mode, std::string mode_params);
int	rpl_notopic(int fd, std::string dest_nick, std::string channel);
int	rpl_topic(int fd, std::string dest_nick, std::string channel, std::string topic);
int	rpl_inviting(int fd, std::string dest_nick, std::string channel, std::string nick);
int	rpl_summoning(int fd, std::string dest_nick, std::string user);
int	rpl_exceptlist(int fd, std::string dest_nick, std::string channel,
	std::string mask);
int	rpl_endofexceptlist(int fd, std::string dest_nick, std::string channel);
int	rpl_version(int fd, std::string dest_nick);
int	rpl_whoreply(int fd, std::string dest_nick, std::string chan,
	std::string user, std::string host, std::string server, std::string nick,
	std::string weird_args, int hop_count, std::string real_name);
int	rpl_endofwho(int fd, std::string dest_nick, std::string name);
// int	rpl_namreply(int fd, std::string dest_nick, Channel chan) // AREVOIR;
int	rpl_endofnames(int fd, std::string dest_nick, std::string channel);
int	rpl_links(int fd, std::string dest_nick, std::string mask,
	std::string server, int hop_count, std::string serv_info);
int	rpl_endoflinks(int fd, std::string dest_nick);
int	rpl_banlist(int fd, std::string dest_nick, std::string channel, std::string banmask);
int	rpl_endofbanlist(int fd, std::string dest_nick, std::string channel);
int	rpl_info(int fd, std::string dest_nick, std::string info);
int	rpl_endofinfo(int fd, std::string dest_nick);
int	rpl_motdstart(int fd, std::string dest_nick);
int	rpl_motd(int fd, std::string dest_nick, std::string msg);
int	rpl_endofmotd(int fd, std::string dest_nick);
int	rpl_youreoper(int fd, std::string dest_nick);
int	rpl_rehashing(int fd, std::string dest_nick, std::string config_file);
int	rpl_time(int fd, std::string dest_nick);
int	rpl_usersstart(int fd, std::string dest_nick);
int	rpl_users(int fd, std::string dest_nick, std::string username,
	std::string ttyline, std::string hostname);
int	rpl_endofusers(int fd, std::string dest_nick);
int	rpl_nousers(int fd, std::string dest_nick);
// int	rpl_tracelink(int fd, std::string dest_nick);
// int	rpl_traceconnecting(int fd, std::string dest_nick);
// int	rpl_tracehandshake(int fd, std::string dest_nick);
// int	rpl_traceunknown(int fd, std::string dest_nick);
// int	rpl_traceoperator(int fd, std::string dest_nick);
// int	rpl_traceuser(int fd, std::string dest_nick);
// int	rpl_traceserver(int fd, std::string dest_nick);
// int	rpl_tracenewtype(int fd, std::string dest_nick);
// int	rpl_tracelog(int fd, std::string dest_nick);
// int	rpl_statslinkinfo(int fd, std::string dest_nick);
// int	rpl_statscommands(int fd, std::string dest_nick);
// int	rpl_statscline(int fd, std::string dest_nick);
// int	rpl_statsnline(int fd, std::string dest_nick);
// int	rpl_statsiline(int fd, std::string dest_nick);
// int	rpl_statskline(int fd, std::string dest_nick);
// int	rpl_statsyline(int fd, std::string dest_nick);
// int	rpl_endofstats(int fd, std::string dest_nick);
// int	rpl_statslline(int fd, std::string dest_nick);
// int	rpl_statsuptime(int fd, std::string dest_nick);
// int	rpl_statsoline(int fd, std::string dest_nick);
// int	rpl_statshline(int fd, std::string dest_nick);
int	rpl_umodeis(int fd, std::string dest_nick, std::string user_mode);
// int	rpl_luserclient(int fd, std::string dest_nick);
// int	rpl_luserop(int fd, std::string dest_nick);
// int	rpl_luserunknown(int fd, std::string dest_nick);
// int	rpl_luserchannels(int fd, std::string dest_nick);
// int	rpl_luserme(int fd, std::string dest_nick);
// int	rpl_adminme(int fd, std::string dest_nick);
// int	rpl_adminloc1(int fd, std::string dest_nick);
// int	rpl_adminloc2(int fd, std::string dest_nick);
// int	rpl_adminemail(int fd, std::string dest_nick);