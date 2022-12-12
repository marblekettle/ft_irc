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
	(void)client;
	(void)arguments;
	std::cout << "Call join command" << std::endl;
	return ;
}

PrivMsgCommand::PrivMsgCommand(Server* server) : Command(server) {}


PrivMsgCommand::~PrivMsgCommand()
{
}

void	PrivMsgCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	std::string name;
	name = arguments[1];
	if (name[0] == '#') // handle channel massage
	{
		Channel* channel;
		channel = _server->getChannel(name.substr(1));
		if (channel)
		{
			// broadcast to channel
			return ;
		}
		// error
	}
	else
	{
		Client* recv_client;
		recv_client =  _server->getClient(name);
		if (recv_client)
		{
			std::stringstream ssMsg;
			std::vector<std::string>::iterator it;
			ssMsg << client->getPrefix();
			for (it = arguments.begin() + 2; it != arguments.end(); it++)
				ssMsg << *it;
			recv_client->reply(ssMsg.str());
			return ;
		}
		// error
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
	std::cout << "Call Nick command" << std::endl;
	if (arguments[0].empty() || arguments[1].empty())
	{
		client->reply(ERR_NONICKNAMEGIVEN(client->getHost()));
		return ;
	}
	
	if (_server->getClient(arguments[1])) {
		client->reply(ERR_NICKNAMEINUSE(client->getHost(), client->getNick()));
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
		ss << *it;
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
