#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include "responses.hpp"

JoinCommand::JoinCommand(Server* server) : Command(server)
{
}

JoinCommand::~JoinCommand()
{
}

void	JoinCommand::execute(std::vector<std::string>& arguments, Client* client)
{ 
	Channel* channel;
	std::string prefix(client->getPrefix());

	if (client->getState() < ACCESS)
	{
		client->reply(ERR_NOTREGISTERED(client->getHost()));
		return ;
	}
	if (arguments[1].empty() || arguments[1][0] != '#')
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getHost(), arguments[0]));
		return ;
	}
	channel = _server->getChannel(arguments[1].substr(1));
	std::stringstream ssNameList;
	if (!channel)
	{
		ssNameList << "#" << client->getNick();
		channel = new Channel(arguments[1].substr(1), client);
		_server->addChannel(channel);
		client->reply(RPL_JOIN(prefix, arguments[1]));
	}
	else
	{
		std::vector<Client *>::iterator it;
		channel->addClient(client);
		for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it)
		{
			if (channel->isAdmin((*it)->getNick()))
				ssNameList << "#" << (*it)->getNick() << " ";
			else
				ssNameList << (*it)->getNick() << " ";
		}
	
		channel->broadCast(RPL_JOIN(prefix, arguments[1]), nullptr);
	}
	client->reply(RPL_NAMREPLY(client->getHost(), client->getNick(), arguments[1], ssNameList.str()));
	client->reply(RPL_ENDOFNAMES(client->getHost(), client->getNick(), arguments[1]));
}

PrivMsgCommand::PrivMsgCommand(Server* server) : Command(server) {}


PrivMsgCommand::~PrivMsgCommand()
{
}

void	PrivMsgCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	std::string name;
	std::string prefix(client->getPrefix());

	name = arguments[1];
	if (arguments[1].empty())
	{
		client->reply(ERR_NORECIPIENT(client->getHost(), arguments[0]));
		return ;
	}
	if (arguments[2].empty())
	{
		client->reply(ERR_NOTEXTOSEND(client->getHost()));
		return ;
	}
	// concat argument strings to ssMsg
	std::stringstream ssMsg;
	std::vector<std::string>::iterator it;
	for (it = arguments.begin() + 2; it != arguments.end(); ++it)
		ssMsg << *it;

	if (name[0] == '#') // handle channel massage
	{
		Channel* channel;
		channel = _server->getChannel(name.substr(1));
		if (channel)
		{
			if (!channel->inClientList(client))
				client->reply(ERR_NOTONCHANNEL(client->getHost(), name));
			else
				channel->broadCast(RPL_PRIVMSG(prefix, name, ssMsg.str()), client);
		}
		else 
			client->reply(ERR_NOSUCHNICK(client->getHost(), name));
		return ;
	}
	else //handle client message
	{
		Client* recv_client;
		recv_client = _server->getClient(name);
		if (recv_client)
			recv_client->reply(RPL_PRIVMSG(prefix, name, ssMsg.str()));
		else
			client->reply(ERR_NOSUCHNICK(client->getHost(), name));
		return ;
	}
}

KickCommand::KickCommand(Server* server) : Command(server) {}

KickCommand::~KickCommand() {}

void	KickCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	(void)client;
	(void)arguments;
	std::cout << "Call Kick command" << std::endl;
	return ;
}

QuitCommand::QuitCommand(Server* server)  : Command(server) {}

QuitCommand::~QuitCommand() {}

void	QuitCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	(void)client;
	(void)arguments;
	std::cout << "Call Quit command" << std::endl;
	return ;
}

ModeCommand::ModeCommand(Server* server) : Command(server) {}

ModeCommand::~ModeCommand() {}

void	ModeCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	(void)client;
	(void)arguments;
	std::cout << "Call mode command" << std::endl;
	return ;
}

NickCommand::NickCommand(Server* server) : Command(server) {}

NickCommand::~NickCommand() {}

void	NickCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	std::string nickname;

	if (client->getState() < AUTHENTICATED)
	{
		client->reply(ERR_NOTREGISTERED(client->getHost()));
		return ;
	}
	if (arguments[0].empty() || arguments[1].empty())
	{
		client->reply(ERR_NONICKNAMEGIVEN(client->getHost()));
		return ;
	}
	
	if (_server->getClient(arguments[1])) {
		client->reply(ERR_NICKNAMEINUSE(client->getHost(), client->getNick(), arguments[1]));
		return ;
	}
	client->setNick(arguments[1]);

	std::string reply_msg;
	reply_msg.append(": NICK :");
	reply_msg.append(arguments[1]);

	client->reply(reply_msg);
	logToServer(reply_msg);
	if (client->getState() < REGISTERED)
	{
		client->welcome();
		client->setState(REGISTERED);
	}
}

UserCommand::UserCommand(Server* server) : Command(server) {}

UserCommand::~UserCommand() {}

void	UserCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	if (client->getState() < REGISTERED)
	{
		client->reply(ERR_NOTREGISTERED(client->getHost()));
		return ;
	}
	client->setUser(arguments[2]);
	std::stringstream ss;
	std::vector<std::string>::iterator it;
	ss << arguments[4].substr(1);
	for (it = arguments.begin() + 5; it != arguments.end(); ++it)
		ss << " " << *it;
	client->setRealName(ss.str());
	client->setState(ACCESS);
	client->welcome();
}

PassCommand::PassCommand(Server* server) : Command(server) {}

PassCommand::~PassCommand() {}

void	PassCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	if (client->getState() > LOGIN)
	{
		client->reply(ERR_ALREADYREGISTRED(client->getHost()));
		return ;
	}
	if (arguments[1].empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getHost(), "PASS"));
		return ;
	}
	if (arguments[1] != _server->getPassword())
	{
		std::cout << "auth failed" << std::endl;
		return ; // get disconected from server, no notification
	}
	client->setState(AUTHENTICATED);
}

PingCommand::PingCommand(Server* server) : Command(server) {}

PingCommand::~PingCommand() {}

void	PingCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	if (arguments[1].empty())
	{
		client->reply(ERR_NOORIGIN(client->getHost()));
		return ;
	}
	client->reply(RPL_PING(client->getHost(), client->getNick()));
}
