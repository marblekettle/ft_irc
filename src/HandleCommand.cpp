#include "HandleCommand.hpp"
#include "utils.hpp"

HandleCommand::HandleCommand(Server* server) : _server(server)
{
	_commands["/JOIN"] = new JoinCommand(_server);
	_commands["/PRIVMSG"] = new PrivMsgCommand(_server);
	_commands["/KICK"] = new KickCommand(_server);
	_commands["/QUIT"] = new QuitCommand(_server);
	_commands["/MODE"] = new ModeCommand(_server);
	_commands["/NICK"] = new NickCommand(_server);
	_commands["/USER"] = new UserCommand(_server);
}

HandleCommand::~HandleCommand()
{
	std::map<std::string, Command*>::iterator it;

	for (it = _commands.begin(); it != _commands.end(); it++)
	{
		delete it->second;
	}
}

/* The Call member function splits the data from a client by spaces, */
/* And place them in a vector.										 */
/* Because the commands of the irc protocol are not case sensitive,  */
/* they get converted to uppercase and then compared.				 */
/* The command comes always after the prefix, if not it's a current  */
/* privat message or current channel message						 */

void	HandleCommand::call(std::string &message, Client* client)
{
	(void)client;

	std::vector<std::string> arguments;
	std::string temp;
	std::istringstream ssMessage(message);
	while (std::getline(ssMessage, temp, ' '))
	{
		// std::cout << "Arguments are: " << temp << std::endl;
		arguments.push_back(temp);
	}
	temp = StringToUpper(arguments[1]);
	Command* cmd;
	if (_commands.count(temp) > 0)
	{
		cmd = _commands.at(temp);
		cmd->execute(arguments, client);
	}
}
