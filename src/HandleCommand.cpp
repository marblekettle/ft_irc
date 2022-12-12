#include "HandleCommand.hpp"
#include "utils.hpp"

HandleCommand::HandleCommand(Server* server) : _server(server)
{
	_commands["JOIN"] = new JoinCommand(_server);
	_commands["PRIVMSG"] = new PrivMsgCommand(_server);
	_commands["KICK"] = new KickCommand(_server);
	_commands["QUIT"] = new QuitCommand(_server);
	_commands["MODE"] = new ModeCommand(_server);
	_commands["NICK"] = new NickCommand(_server);
	_commands["USER"] = new UserCommand(_server);
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
	std::string temp;
	std::string cut = message.substr(0, message.find('\n'));
	size_t				pos = 0;
	std::vector<t_str>	v;
	while (1) {
		size_t	pos2;
		if (cut[pos] == ':') {
			pos++;
			pos2 = cut.size();
			while (pos2 > 1 && cut[pos2 - 1] == ' ')
				pos2--;
		} else
			pos2 = cut.find(' ', pos);
		t_str split = cut.substr(pos, pos2 - pos);
		if (split.size() > 0)
			v.push_back(split);
		if (pos2 >= cut.size())
			break ;
		pos = pos2 + 1;
	}
	_args = v;
	temp = StringToUpper(v[0]);
	Command* cmd;
	if (_commands.count(temp) > 0) {
		cmd = _commands.at(temp);
		if (client)
			cmd->execute(v, client);
	}
}

size_t	HandleCommand::getNArgs() const {
	return (_args.size());
}

t_str	HandleCommand::getArg(size_t n) const {
	return (_args.at(n));
}
