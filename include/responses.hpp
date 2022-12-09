#ifndef RESPONSES_HPP
#define RESPONSES_HPP

/* Messages on succes */

#define RPL_WELCOME(server, prefix, nick) 	server + "001 " + nick + " :Welcome to the Internet Relay Network " + prefix
/* Error messages */

#define ERR_NICKNAMEINUSE(server,nick)		server + " 433 * " + nick + " :Nickname is already in use."
#define ERR_ALREADYREGISTRED(server)		"462 " + server + " :You may not reregister"
#define ERR_PASSWDMISMATCH(server) 			"464 " + server + " :irc.example.com 464 chris :Password Incorrect"
#define	ERR_NEEDMOREPARAMS(server, command) "461 " + server + " " + command + " :Not enough parameters"

#endif /* RESPONSES_HPP */