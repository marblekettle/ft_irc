#include "Command.hpp"

JoinCommand::JoinCommand(Server* server) : Command(server)
{
}

JoinCommand::~JoinCommand()
{
}

void	JoinCommand::execute(std::vector<std::string> arguments)
{
	(void)arguments;
	std::cout << "Call join command" << std::endl;
	return ;
}

PrivMsgCommand::PrivMsgCommand(Server* server) : Command(server) {}


PrivMsgCommand::~PrivMsgCommand()
{
}

void	PrivMsgCommand::execute(std::vector<std::string> arguments)
{
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
		clientToRecieve->sendMessage(ssMsg.str());
	}
	return ;
}

KickCommand::KickCommand(Server* server) : Command(server) {}

KickCommand::~KickCommand()
{
}

void	KickCommand::execute(std::vector<std::string> arguments)
{
	(void)arguments;
	std::cout << "Call Kick command" << std::endl;
	return ;
}

QuitCommand::QuitCommand(Server* server)  : Command(server)
{
}

QuitCommand::~QuitCommand()
{
}

void	QuitCommand::execute(std::vector<std::string> arguments)
{
	(void)arguments;
	std::cout << "Call Quit command" << std::endl;
	return ;
}

ModeCommand::ModeCommand(Server* server) : Command(server)
{
}

ModeCommand::~ModeCommand()
{
}

void	ModeCommand::execute(std::vector<std::string> arguments)
{
	(void)arguments;
	std::cout << "Call Kick command" << std::endl;
	return ;
}
