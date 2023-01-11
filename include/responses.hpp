#ifndef RESPONSES_HPP
#define RESPONSES_HPP
/* Messages on succes */

#define RPL_WELCOME(source, nick) 	":" + source + " 001 " + nick + " :Welcome to the Internet Relay Network, " + nick
#define RPL_MODE(prefix, channel, nick, message) prefix + " MODE " + nick + " " + channel + " " + message
// #define RPL_CHANNELMODEIS(prefix, channel, message) prefix + " MODE " + nick + " " + channel + " " + message
#define RPL_JOIN(prefix, channel)	prefix + " JOIN " + channel
#define RPL_PART(prefix, channel, message)	prefix + " PART " + channel + " " + message
#define RPL_KICK(prefix, channel, nick, message) prefix + " PART " + channel + " " + nick + " " + message
#define	RPL_PRIVMSG(prefix, recipient, message)				prefix + " PRIVMSG " + recipient + " " + message
#define RPL_PING(source, nick)		source + " PONG " + nick
/* Error messages */


#define RPL_NAMREPLY(source, nick, channel, namelist)	":" + source + " 353 " + nick + " = " + channel + " :" + namelist
#define RPL_ENDOFNAMES(source, nick, channel)			":" + source + " 366 " + channel + " :End of NAMES list"
#define ERR_NOSUCHNICK(source, nick)		":" + source + " 401 " + nick + " :No such nick/channel"
#define ERR_NOSUCHCHANNEL(source, channel)	":" + source + " 403 " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(source, nick, channel)	":" + source + " 404 " + nick + channel + " :Cannot send to channel"
#define ERR_NOORIGIN(source)				":" + source + " 409 :No origin specified"
#define ERR_NORECIPIENT(source, command)	":" + source + " 411 :No recipient given (" + command + ")"
#define ERR_NOTEXTOSEND(source)				":" + source + " 412 :No text to send"
#define ERR_UNKNOWNCOMMAN(source, command)	":" + source + " 421 " + command + " :Unknown command"
#define ERR_NONICKNAMEGIVEN(source)			":" + source + " 431 :Nickname not given"
#define ERR_NICKNAMEINUSE(source, nick, new_nick)		":" + source + " 433 " + nick + new_nick + " " + " :Nickname is already in use."
#define ERR_USERNOTINCHANNEL(source, nick, channel)	":" + source + " 441 " + nick + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(source,channel)	":" + source + " 442 " + channel + " :You're not on that channel"
#define ERR_NOTREGISTERED(source)			":" + source + " 451 :You have not registered"
#define	ERR_NEEDMOREPARAMS(source, command) ":" + source + " 461 " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTRED(source)		":" + source + " 462 :You may not reregister"
#define ERR_PASSWDMISMATCH(source) 			":" + source + " 464 :Password Incorrect"
#define ERR_UNKNOWNMODE(source, modechar, channel)	":" + source + " 472 " + modechar + " :is unknown mode char to me for " + channel
#define ERR_KEYSET(source,channel)			":" + source + " 467 " + channel + " :Channel key already set"
#define ERR_CHANNELISFULL(source,channel)	":" + source + " 471 " + channel + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(source,channel)	":" + source + " 473 " + channel + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(source,channel)	":" + source + " 475 " + channel + " :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED(source, channel)	":" + source + " 482 " + channel + " :You're not channel operator"
#endif /* RESPONSES_HPP */
