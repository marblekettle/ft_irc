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
	(void)client;
	std::cout << "Call Private Msg command" << std::endl;
	Client*		clientToRecieve;
	std::string name;
	name = arguments[2];
	clientToRecieve =  _server->getClient(name);
	if (clientToRecieve)
	{
		std::stringstream ssMsg;
		std::vector<std::string>::iterator it;
		for (it = arguments.begin() + 2; it != arguments.end(); it++)
			ssMsg << *it;
		// ssMsg = client->getPrefix() + ssMsg;
		clientToRecieve->sendMessage(ssMsg.str());
	}
	return ;
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
	// client->welcome();
}

UserCommand::UserCommand(Server* server) : Command(server) {}

UserCommand::~UserCommand() {}

void	UserCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	std::cout << "Call User command" << std::endl;

	std::string user = StringToUpper(arguments[2]);
	Client* tmp_client = _server->getClient(user);
	if (!tmp_client)
		client->setUser(user);
	else
		client->sendMessage("USERNAME already exist on server");
	return ;
}
