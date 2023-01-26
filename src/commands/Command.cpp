#include "Command.hpp"

PrivMsgCommand::PrivMsgCommand(Server* server) : Command(server) {}


PrivMsgCommand::~PrivMsgCommand()
{
}

void	PrivMsgCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	std::string name;
	std::string prefix(client->getPrefix());

	if (client->getState() < ACCESS)
	{
		client->reply(ERR_NOTREGISTERED(client->getHost()));
		return ;
	}
	if (arguments[1].empty())
	{
		client->reply(ERR_NORECIPIENT(client->getHost(), arguments[0]));
		return ;
	}
	name = arguments[1];
	if (arguments[2].empty())
	{
		client->reply(ERR_NOTEXTOSEND(client->getHost()));
		return ;
	}
	// concat argument strings to ssMsg
	std::stringstream ssMsg;
	std::vector<std::string>::iterator it;
	for (it = arguments.begin() + 2; it != arguments.end(); ++it)
		ssMsg << *it;

	if (name[0] == '#') // handle channel massage
	{
		Channel* channel;
		channel = _server->getChannel(name.substr(1));
		if (channel)
		{
			if (!channel->inClientList(client))
				client->reply(ERR_CANNOTSENDTOCHAN(client->getHost(), client->getNick(), name));
			else
				channel->broadCast(RPL_PRIVMSG(prefix, name, ssMsg.str()), client);
		}
		else 
			client->reply(ERR_NOSUCHNICK(client->getHost(), name));
		return ;
	}
	else //handle client message
	{
		Client* recv_client;
		recv_client = _server->getClient(name);
		if (recv_client)
			recv_client->reply(RPL_PRIVMSG(prefix, name, ssMsg.str()));
		else
			client->reply(ERR_NOSUCHNICK(client->getHost(), name));
		return ;
	}
}

KickCommand::KickCommand(Server* server) : Command(server) {}

KickCommand::~KickCommand() {}

void	KickCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	Channel* channel;
	Client*	client_kick;

	size_t nb_of_args = arguments.size();
	if (client->getState() < ACCESS)
	{
		client->reply(ERR_NOTREGISTERED(client->getHost()));
		return ;
	}
	if (nb_of_args < 3 || arguments[1][0] != '#')
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getHost(), arguments[0]));
		return ;
	}
	channel = _server->getChannel(arguments[1].substr(1));

	if (!channel)
	{
		client->reply(ERR_NOSUCHCHANNEL(client->getHost(), arguments[1].substr(1)));
		return ;
	}
	client_kick = channel->getClient(arguments[2]);
	if (!channel->inClientList(client) || !client_kick)
	{
		client->reply(ERR_NOTONCHANNEL(client->getHost(), arguments[1].substr(1)));
		return ;
	}
	if (!channel->isAdmin(client))
	{
		client->reply(ERR_CHANOPRIVSNEEDED(client->getHost(), arguments[1].substr(1)));
		return ;
	}
	channel->removeClient(client_kick);
	client_kick->popChannel(channel);
	std::string msg;
	msg = (arguments.size() > 3) ? arguments[3] : "";
	channel->broadCast(RPL_KICK(client->getPrefix(), arguments[1], arguments[2], msg), client);
	return ;
}

QuitCommand::QuitCommand(Server* server)  : Command(server) {}

QuitCommand::~QuitCommand() {}

void	QuitCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	t_chan_iter	it;
	t_str		message;

	if (client->getState() < ACCESS)
	{
		client->reply(ERR_NOTREGISTERED(client->getHost()));
		return ;
	}
	if (arguments.size() > 1)
		message = arguments[1];
	else
		message = "";
	for (it = client->getActiveChannelBegin(); it != client->getActiveChannelEnd(); ++it)
	{
		(*it)->removeClient(client);
		if ((*it)->getClientList().size() < 1)
			_server->popChannel(*it);
		else
			(*it)->broadCast(RPL_QUIT(client->getPrefix(), message));
	}
	client->clearActiveChannels();
	_server->disconnectClient(client->getFd());
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
	if (arguments[0].empty() || arguments[1].empty())
	{
		client->reply(ERR_NONICKNAMEGIVEN(client->getHost()));
		return ;
	}
	
	if (_server->getClient(arguments[1])) {
		client->reply(ERR_NICKNAMEINUSE(client->getHost(), client->getNick(), arguments[1]));
		return ;
	}
	client->setNick(arguments[1]);

	std::string reply_msg;
	reply_msg.append(": NICK :");
	reply_msg.append(arguments[1]);

	client->reply(reply_msg);
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
	std::vector<std::string>::iterator it;
	std::stringstream ss;
	ss << arguments[4].substr(1);
	for (it = arguments.begin() + 5; it != arguments.end(); ++it)
		ss << " " << *it;
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
		// _server->disconnectClient(client->getFd());
		return ; // get disconected from server, no notification
	}
	client->setState(AUTHENTICATED);
}

PingCommand::PingCommand(Server* server) : Command(server) {}

PingCommand::~PingCommand() {}

void	PingCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	if (arguments[1].empty())
	{
		client->reply(ERR_NOORIGIN(client->getHost()));
		return ;
	}
	client->reply(RPL_PING(client->getHost(), client->getNick()));
}

PartCommand::PartCommand(Server* server) : Command(server) {}

PartCommand::~PartCommand() {}

void	PartCommand::execute(std::vector<std::string>& arguments, Client* client)
{
	Channel* channel;

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
	if (!channel)
	{
		client->reply(ERR_NOSUCHCHANNEL(client->getHost(), arguments[1].substr(1)));
		return ;
	}
	if (!channel->inClientList(client))
	{
		client->reply(ERR_NOTONCHANNEL(client->getHost(), channel->getName()));
		return ;
	}
	std::string msg;
	msg = (arguments.size() > 2) ? arguments[2] : "";

	channel->removeClient(client);
	client->popChannel(channel);
	channel->broadCast(RPL_PART(client->getPrefix(), arguments[1], msg));
	if (channel->getClientList().size() < 1)
		_server->popChannel(channel);
}
