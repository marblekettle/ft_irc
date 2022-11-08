#include "Command.hpp"

JoinCommand::JoinCommand()
{
}

JoinCommand::~JoinCommand()
{
}

void	JoinCommand::execute()
{
	std::cout << "Call join command" << std::endl;
	return ;
}

PrivMsgCommand::PrivMsgCommand()
{
}

PrivMsgCommand::~PrivMsgCommand()
{
}

void	PrivMsgCommand::execute()
{
	std::cout << "Call Private Msg command" << std::endl;
	return ;
}

KickCommand::KickCommand()
{
}

KickCommand::~KickCommand()
{
}

void	KickCommand::execute()
{
	std::cout << "Call Kick command" << std::endl;
	return ;
}

QuitCommand::QuitCommand()
{
}

QuitCommand::~QuitCommand()
{
}

void	QuitCommand::execute()
{
	std::cout << "Call Quit command" << std::endl;
	return ;
}

ModeCommand::ModeCommand()
{
}

ModeCommand::~ModeCommand()
{
}

void	ModeCommand::execute()
{
	std::cout << "Call Kick command" << std::endl;
	return ;
}
