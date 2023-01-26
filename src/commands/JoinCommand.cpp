#include "Command.hpp"

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
	size_t	nb_of_args = arguments.size();

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
		client->addChannel(channel);
		if (nb_of_args == 3)
			channel->setPassword(arguments[2]);
		client->reply(RPL_JOIN(prefix, arguments[1]));
	}
	else
	{
		std::vector<Client *>::iterator it;
		if (static_cast<int>(channel->getClientList().size()) >= channel->getLimit())
		{
			client->reply(ERR_CHANNELISFULL(client->getHost(), channel->getName()));
			return ;
		}
		if (channel->getPassword().size() > 0)
		{
			if (nb_of_args < 3 || arguments[2] != channel->getPassword())
			{
				client->reply(ERR_BADCHANNELKEY(client->getHost(), arguments[1].substr(1)));
				return ;
			}
			channel->setPassword(arguments[2]);
		}
		channel->addClient(client);
		client->addChannel(channel);
		for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it)
		{
			if (channel->isAdmin(*it))
				ssNameList << "#" << (*it)->getNick() << " ";
			else
				ssNameList << (*it)->getNick() << " ";
		}
		channel->broadCast(RPL_JOIN(prefix, arguments[1]));
	}
	channel->broadCast(RPL_NAMREPLY(client->getHost(), client->getNick(), arguments[1], ssNameList.str()));
	channel->broadCast(RPL_ENDOFNAMES(client->getHost(), client->getNick(), arguments[1]));
}
