#include "Server.hpp"
#include "HandleCommand.hpp"
#include "Client.hpp"
#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(t_port port, t_str passwd):
	_port(port),
	_passwd(passwd),
	_ready(false),
	_sendready(false)
{
	_socket = openSocket();
	_handleCommand = new HandleCommand(this);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
	disconnectAllClients();
	clearAllChannels();
	delete _handleCommand;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool	Server::connectClient() 
{
	int	fd;
	t_addr	addr;								//IP address stored in here
	std::memset(&addr, 0, sizeof(t_addrin));
	socklen_t	addrlen = sizeof(t_addr);
	fd = accept(_socket, &addr, &addrlen);	//Get new file descriptor
	if (fd < 0)
		throw std::runtime_error("Error");
	if (addrlen != sizeof(t_addr)) {	//Kicks out connection if not correct protocol
		close (fd);
		throw std::runtime_error("Error");
	}
	fcntl(fd, F_SETFL, O_NONBLOCK);	//Set FD to non-blocking
	t_fd	pollfd = {fd, POLLIN, 0};
	_fd.push_back(pollfd);
	_addrmap[pollfd.fd] = *(reinterpret_cast<t_addrin*>(&addr));
	char hostname[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
		throw std::runtime_error("Error");
	Client* client = new Client(fd, hostname);
	_clients.insert(std::make_pair(fd, client));
	std::cout << "client #" << fd << " is connected" << std::endl;
	std::cout << "Host: " << client->getHost() << std::endl;
	return (true);
}

void	Server::addChannel(Channel * channel) {

	_channels.insert(std::make_pair(channel->getName(), channel));
	std::cout << "Channel: '" << channel->getName() << "' added" << std::endl;
}

void	Server::popChannel(Channel* channel) {

	_channels.erase(channel->getName());
	delete channel;
}

void	Server::clearAllChannels()
{
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		delete it->second;
	_channels.clear();
}

void	Server::__queue(int fd, t_str data) {
	t_datap	datap;
	datap.first = fd;
	datap.second = data;
	_dataq.push(datap);
}

int		Server::openSocket() 
{
	int		socket_fd;
	socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		throw std::runtime_error("Error");
	int val = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");
	if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) < 0) //Set listening FD to non-blocking
		throw std::runtime_error("Error");

	t_addrin serv_addr;
	std::memset(&serv_addr, 0, sizeof(t_addrin));
	serv_addr.sin_family = AF_INET;					//Internet protocol
	serv_addr.sin_port = htons(_port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_fd, reinterpret_cast<t_addr*>(&serv_addr), sizeof(t_addr)))
		throw std::runtime_error("Error");
	
	if (listen(socket_fd, 10) < 0)						//Set listening FD to listen
		throw std::runtime_error("Error");
	_ready = true;
	return (socket_fd);
}

void		Server::run() 
{
	t_fd	server_fd = {_socket, POLLIN, 0};
	_fd.push_back(server_fd);
	while (_ready) 
	{
		__togglepoll();
		t_fdv::iterator it_end = _fd.end();
		if (poll(_fd.begin().base(), _fd.size(), 1000) < 0)
			throw std::runtime_error("Poll Error");
		for (t_fdv::iterator it = _fd.begin(); it != it_end; it++) {
			if (it->revents == 0)
				continue;
			if (it->revents & (POLLHUP | POLLNVAL | POLLERR)) {
				std::cout << "FD " << it->fd << " disconnected!" << std::endl;
				disconnectClient(it->fd);
				continue ;
			}
			if (it->revents & POLLIN) {
				if (it->fd == _socket) {
					connectClient();
					continue ;
				}
				clientMessage(it->fd); 
			}
			if (it->revents & POLLOUT) {
				Client*	cl = _clients[it->fd];
				if (cl && cl->nResponses() > 0) {
					t_str tosend = cl->popResponse();
					int sent = send(it->fd, tosend.c_str(), tosend.size(), 0);
					if (static_cast<unsigned int>(sent) != tosend.size())
						std::cerr << "Error: Whole message not sent" << std::endl;
				}
			}
		}
		while (_dataq.size() > 0) {
			int clfd = _dataq.front().first;
			Client*	cl = _clients[clfd];
			if (cl)
				_handleCommand->call(_dataq.front().second, cl);
			_dataq.pop();
		}
	}
}

void	Server::stop() {
	_ready = false;
}

void	Server::clientMessage(int fd)
{
	Client *client = _clients.at(fd);
	t_str message;
	while (client->readMessages(message))
		__queue(fd, message);
}

void	Server::disconnectClient(int fd) 
{
	Client* client = _clients.at(fd);

	std::map<std::string, Channel *>::const_iterator iter;
	for (iter = _channels.cbegin(); iter != _channels.cend() ;)
	{
		iter->second->removeClient(client);
		if (iter->second->getClientList().size() < 1) {
			delete iter->second;
			_channels.erase(iter++);
		}
		else
		{
			iter->second->broadCast(RPL_QUIT(client->getPrefix(), "DISCONNECTED"));
			++iter;
		}
	}

	_clients.erase(fd);
	t_fdv::const_iterator it;
	for (it = _fd.cbegin(); it != _fd.cend() ;)
	{
		if (it->fd == fd)
		{
			_fd.erase(it++);
			close(fd);
			break ;
		}
		else
			++it;
	}
	delete client;
}

void		Server::disconnectAllClients()
{
	for (t_clients::iterator it = _clients.begin(); it != _clients.end(); it++) {
		it->second->reply(RPL_QUIT(it->second->getHost(), ":SERVER DISCONNECTING"));
		delete it->second;
	}
	_clients.clear();

	for (t_fdv::iterator it = _fd.begin(); it != _fd.end(); it++) {
		close(it->fd);
	}
	_fd.clear();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int		Server::getQueuedData(t_datap& data) {
	int siz = _dataq.size();
	if (siz) {
		data = _dataq.front();
		_dataq.pop();
	}
	return (siz);
}

t_str	Server::getIP(int fd) {
	try {
		t_str out = inet_ntoa(_addrmap.at(fd).sin_addr);
		return (out);
	} catch(std::exception &e) {
		return ("");
	}
}

std::string		Server::getPassword() const
{
	return (this->_passwd);
}

uint32_t	Server::getPort() const
{
	return (this->_port);
}

Client*		Server::getClient(std::string& nickname) const
{
	t_clients::const_iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second->getNick() == nickname)
			return (it->second);
	}
	return (nullptr);
}

t_clients	Server::getClients() const
{
	return (_clients);
}

Channel*	Server::getChannel(std::string chan_name)
{
	std::map<std::string, Channel *>::iterator it;

	it = _channels.find(chan_name);
	if (it != _channels.end())
		return (it->second);
	return (nullptr);
}

const char*	Server::socketFailedError::what() const throw() {
	return ("Socket failed");
}

const char*	Server::connectionError::what() const throw() {
	return ("Connection error");
}

void	Server::__togglepoll() {
	for (unsigned int i = 1; i < _fd.size(); i++) {
		_fd[i].events = _sendready ? POLLOUT : POLLIN;
	}
	_sendready = _sendready ? false : true;
}
