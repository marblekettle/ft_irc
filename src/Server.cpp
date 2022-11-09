#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(t_port port, t_str password):
	_port(port),
	_password(password),
	_ready(false) 
{
	_socket = openSocket();
	_handleCommand = new HandleCommand(this);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
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
	// pollfd.events = (POLLIN | POLLOUT);		//Allow for sending AND receiving data
	pollfd.events = (POLLIN);		//Allow for sending AND receiving data
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
	serv_addr.sin_addr.s_addr = htonl(0x7F000001);	//Localhost/127.0.0.1
	// serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket_fd, reinterpret_cast<t_addr*>(&serv_addr), sizeof(t_addr)))
		throw std::runtime_error("Error");
	
	if (listen(socket_fd, 10) < 0)						//Set listening FD to listen
		throw std::runtime_error("Error");
	return (socket_fd);
}

void		Server::run() 
{
	t_fd	server_fd = {_socket, POLLIN, 0};
	_fd.push_back(server_fd);
	while (1) 
	{
		t_fdv::iterator it_end = _fd.end();
		if (poll(_fd.begin().base(), _fd.size(), -1) < 0)
			throw std::runtime_error("Error");
		for (t_fdv::iterator it = _fd.begin(); it != it_end; it++) {
			if (it->revents == 0)
				continue;
			if ((it->revents & POLLHUP) == POLLHUP) {
				std::cout << "FD " << it->fd << " disconnected!" << std::endl;
				disconnectClient(it->fd);
				break ;
			}
			if (it->revents & POLLIN) {
				if (it->fd == _socket) {
					connectClient();
					break ;
				}
				clientMessage(it->fd); 
			}
		}
	}	
}


std::string		Server::readMessage(int fd)
{
	t_str	message;
	char	buf[100];

	bzero(buf, 100);
	while (!std::strstr(buf, "\n"))
	{
		if (recv(fd, buf, 100, 0) < 0)
		{
			if (errno != EWOULDBLOCK)
				throw (std::runtime_error("Error with reading buf from client"));
		}
		message.append(buf);
	}
	// __queue(fd, message);
	std::cout << "Client #" << fd << " :" << message ;
	return (message);
}

void	Server::clientMessage(int fd)
{
	Client *client = _clients.at(fd);
	std::string message;
	message = readMessage(fd);
	_handleCommand->call(message, client);
	// broadcast(fd, readMessage(fd));
}

void	Server::broadcast(int fd, std::string message)
{
	std::ostringstream ss;

	ss << "From client #" << fd << " : "<< message;

	std::map<int, Client*>::iterator it;

	for (it = (_clients.begin()); it != _clients.end(); ++it)
	{
		if (it->first == fd || it->first == _socket)
			continue;
		send(it->first, ss.str().c_str(), ss.str().size() + 1, 0);
	}
}

void	Server::disconnectClient(int fd) 
{
	Client* client = _clients.at(fd);
	_clients.erase(fd);
	t_fdv::iterator it;
	for (it = _fd.begin(); it != _fd.end(); it++)
	{
		if (it->fd == fd)
		{
			_fd.erase(it);
			close(fd);
			break ;
		}
	}
	delete client;
}

/*
** --------------------------------- MUTATORS ---------------------------------
*/


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
	return (this->_password);
}

uint32_t	Server::getPort() const
{
	return (this->_port);
}

Client*		Server::getClient(std::string& username) const
{
	t_clients::const_iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second->getUser() == username)
			return (it->second);
	}
	
	return (nullptr);
}

t_clients	Server::getClients() const
{
	return (_clients);
}

// int		Server::getConnections(t_conn& conn) {
// 	int	siz = _connq.size();
// 	if (siz) {
// 		conn = _connq.front();
// 		_connq.pop();
// 	}
// 	return (siz);
// }

const char*	Server::socketFailedError::what() const throw() {
	return ("Socket failed");
}

const char*	Server::connectionError::what() const throw() {
	return ("Connection error");
}
