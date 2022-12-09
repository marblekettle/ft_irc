#ifndef RESPONSES_HPP
#define RESPONSES_HPP

/* Messages on succes */

#define RPL_WELCOME(source) 	source + "001 " + source + " :Welcome to the Internet Relay Network"
/* Error messages */

#define ERR_NICKNAMEINUSE(source,nick)		source + " 433 * " + nick + " :Nickname is already in use."
#define ERR_ALREADYREGISTRED(source)		"462 " + source + " :You may not reregister"
#define ERR_PASSWDMISMATCH(source) 			"464 " + source + " :irc.example.com 464 chris :Password Incorrect"
#define	ERR_NEEDMOREPARAMS(source, command) "461 " + source + " " + command + " :Not enough parameters"
#define ERR_NONICKNAMEGIVEN(source)			"431 " + source + " :Nickname not given"
#endif /* RESPONSES_HPP */
