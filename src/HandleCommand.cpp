#include "HandleCommand.hpp"
#include "utils.hpp"

HandleCommand::HandleCommand()
{
	_commands["/JOIN"] = new JoinCommand;
	_commands["/PRIVMSG"] = new PrivMsgCommand;
	_commands["/KICK"] = new KickCommand;
	_commands["/QUIT"] = new QuitCommand;
	_commands["/MODE"] = new ModeCommand;
	_commands["/NICK"] = new ModeCommand;
}

HandleCommand::~HandleCommand()
{
	std::map<std::string, Command*>::iterator it;

	for (it = _commands.begin(); it != _commands.end(); it++)
	{
		delete it->second;
	}
}

void	HandleCommand::call(std::string &message, Client* client)
{
	(void)client;
	std::vector<std::string> arguments;
	std::string temp;
	std::istringstream ssMessage(message);
	while (std::getline(ssMessage, temp, ' '))
	{
		std::cout << "Arguments are: " << temp << std::endl;
		arguments.push_back(temp);
	}
	temp = StringToUpper(arguments[1]);
	Command* cmd;
	if (_commands.count(temp) > 0)
	{
		cmd = _commands.at(temp);
		cmd->execute();
	}
}
