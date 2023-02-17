#include "Command.hpp"

typedef	bool (ModeCommand::*mode)(std::vector<std::string>& arguments, Client* client, Channel *channel);

ModeCommand::ModeCommand(Server* server) : Command(server) {}

ModeCommand::~ModeCommand() {}

/* i : Make the channel invite only - existing users will need to invite new users before they can join the channel: /mode $chan +i 
   k : Give the channel a password or key - users will need to provide the key to join the channel: /mode $chan +k key 
   l : Set a limit to the number of users allowed in the channel - 
   			this is typically used to prevent DoS attacks by hundreds of users attempting to join a channel at once, 
				and is reset by a bot as the number of valid users increases as they join or decreases as they part: /mode $chan +l n
   o : Give a user Op status in the channel - usually indicated with nick prefixed with an @: /mode $chan +o nick
 */


void	ModeCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	size_t nb_of_args = arguments.size();
	std::map<char, mode> table;
	table['i'] = &ModeCommand::chanInvite;
	table['k'] = &ModeCommand::chanKey;
	table['l'] = &ModeCommand::chanLimit;
	table['o'] = &ModeCommand::chanOper;

	if (client->getState() < ACCESS)		
		return client->reply(ERR_NOTREGISTERED(client->getHost()));
	if (nb_of_args < 4)
		return client->reply(ERR_NEEDMOREPARAMS(client->getHost(), arguments[0]));
	if (arguments[1][0] == '#')
	{
		// channel modes
		Channel* channel;
		channel = _server->getChannel(arguments[1].substr(1));
		if (!channel)
			return client->reply(ERR_NOSUCHCHANNEL(client->getHost(), arguments[1].substr(1)));
		if (!channel->inClientList(client))
			return client->reply(ERR_NOTONCHANNEL(client->getHost(), channel->getName()));
		if (arguments[2].size() != 2 || !strchr("iklo", arguments[2][1]) || !strchr("+-", arguments[2][0]))
			return client->reply(ERR_UNKNOWNMODE(client->getHost(), arguments[2], arguments[1].substr(1)));
		if (!channel->isAdmin(client))
			return client->reply(ERR_CHANOPRIVSNEEDED(client->getHost(), channel->getName()));
		mode exec = table[arguments[2][1]];

		/* Call member function pointer, 
		   if true the broadcast get called to inform the mode change on the channel. */
		if ((this->*exec)(arguments, client, channel))
			channel->broadCast(RPL_MODE(client->getPrefix(), arguments[1], client->getNick(), ":" + arguments[2]));
		return ;
	}
	else
	{
		// user modes
		return client->reply(ERR_UNKNOWNMODE(client->getHost(), arguments[2], arguments[1].substr(1)));
	}
}

bool		ModeCommand::chanInvite(std::vector<std::string>& arguments, Client* client, Channel* channel)
{
	(void)channel;
	client->reply(ERR_UNKNOWNMODE(client->getHost(), arguments[2], arguments[1].substr(1)));
	return (false);
}

bool		ModeCommand::chanKey(std::vector<std::string>& arguments, Client* client, Channel* channel)
{
	std::string key;

	char sign = arguments[2][0];
	if (sign == '+')
	{
		key = arguments[3];
		if (channel->getPassword().size() > 0)
		{
			client->reply(ERR_KEYSET(client->getHost(), channel->getName()));
			return (false);
		}
		channel->setPassword(key);
		return (true);
	}
	else if (sign == '-')
	{
		key = "";
		if (arguments[3] != channel->getPassword())
		{
			client->reply(ERR_PASSWDMISMATCH(client->getHost()));
			return (false);
		}
		channel->setPassword(key);
		return (true);
	}
	client->reply(ERR_UNKNOWNMODE(client->getHost(), arguments[2], arguments[1].substr(1)));
	return (false);
}

bool		ModeCommand::chanLimit(std::vector<std::string>& arguments, Client* client, Channel* channel)
{
	std::string key;
	std::string limit;

	(void)client;
	char sign = arguments[2][0];
	limit = arguments[3];
	if (sign == '+')
		channel->setLimit(atoi(limit.c_str()));
	else if (sign == '-')
		channel->setLimit(-1);
	else {
		client->reply(ERR_UNKNOWNMODE(client->getHost(), arguments[2], arguments[1].substr(1)));
		return (false);
	}

	return (true);
}

bool		ModeCommand::chanOper(std::vector<std::string>& arguments, Client* client, Channel* channel)
{
	char sign = arguments[2][0];
	Client* new_oper = channel->getClient(arguments[3]);

	if (!new_oper)
	{
		client->reply(ERR_USERNOTINCHANNEL(client->getHost(), arguments[3], channel->getName()));
		return (false);
	}
	if (sign == '+')
	{
		channel->addAdmin(new_oper);
		return (true);
	}
	if (sign == '-')
	{
		if (!channel->isAdmin(new_oper))
		{
			/* Maybe not the right error message but couldn't find a more suitible one */
			client->reply(ERR_NOSUCHNICK(client->getHost(), new_oper->getNick()));
			return (false);
		}
		channel->removeAdmin(new_oper);
		return (true);
	}
	return (false);
}
