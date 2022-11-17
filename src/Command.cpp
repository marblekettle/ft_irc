#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"

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
	name = arguments[1];
	std::cerr << name << std::endl;
	clientToRecieve =  _server->getClient(name);
	std::cerr << clientToRecieve << std::endl;
	if (clientToRecieve)
	{
		std::stringstream ssMsg;
		std::vector<std::string>::iterator it;
		for (it = arguments.begin() + 2; it != arguments.end(); it++)
			ssMsg << *it;
		ssMsg << std::endl;
		clientToRecieve->queueResponse(ssMsg.str());
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
	std::string nick = StringToUpper(arguments[1]);
	std::cerr << nick << std::endl;
	t_clients	clientslist = _server->getClients();
	for (t_clients::iterator it = clientslist.begin(); it != clientslist.end(); it++)
	{
		if (it->second == client)
			continue;
		if (it->second->getNick() == nick)
		{
			client->sendMessage("USERNAME already exist on server");
			return ;
		}
	}
	client->setNick(nick);
	std::cout << "NICK SET" << std::endl;
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
