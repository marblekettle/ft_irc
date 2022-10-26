#include "Server.hpp"
#include <sstream>

Server::Server(t_port port, t_str passwd): \
	_port(port), _passwd(passwd), _ready(false) {
	if (!openSocket(port, passwd))
		throw (socketFailedError());
}

Server::~Server() {};

bool	Server::openSocket(t_port port, t_str passwd) {
	t_fd	fd;
	fd.fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd.fd == -1)
		return (false);
	fcntl(fd.fd, F_SETFL, O_NONBLOCK);
	fd.events = POLLIN;
	t_addrin addr;
	std::memset(&addr, 0, sizeof(t_addrin));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(0x7F000001);
	if (bind(fd.fd, reinterpret_cast<t_addr*>(&addr), sizeof(t_addr)))
		return (false);
	if (_fd.size() == 0)
		_fd.push_back(fd);
	if (listen(fd.fd, 10))
		return (false);
	_port = port;
	_passwd = passwd;
	return (true);
}

int		Server::pollClients() {
	int pollout = poll(_fd.data(), _fd.size(), 1000);
	if (pollout < 0)
		return (-1);
	if (pollout > 0) {
		for (t_fdv::iterator it = _fd.begin() + 1; it < _fd.end(); it++) {
			if (it->revents & POLLIN) {
				char	buf[2000];
				int		len = recv(it->fd, buf, 1999, 0);
				buf[len] = '\0';
				t_str	message(buf);
				message = message.substr(0, message.find('\n'));
				if (_cmap[it->fd].reg)
					sendToAllExcept(message, it->fd);
				else {
					if (message.length() == 0 || message.length() > 15 \
						|| message.find(' ') != std::string::npos) {
						send(it->fd, "Invalid nickname, enter again\n", 30, 0);
					} else {
						memcpy(_cmap.at(it->fd).nick, message.c_str(), message.size());
						send(it->fd, "Nickname registered\n", 20, 0);
						_cmap[it->fd].reg = true;
					}
				}
			}
			if (it->revents & (POLLERR | POLLHUP | POLLNVAL)) {
				std::cout << "FD " << it->fd << " disconnected!" << std::endl;
				close(it->fd);
				_fd.erase(it);
				_cmap.erase(it->fd);
				it--;
			}
		}
		if (_fd[0].revents & POLLIN) {
			t_addr		addr;
			std::memset(&addr, 0, sizeof(t_addrin));
			socklen_t	addrlen;
			int			newfd = accept(_fd[0].fd, &addr, &addrlen);
			if (!addFileDesc(newfd))
				return (-1);
			t_str	cip = inet_ntoa(reinterpret_cast<t_addrin*>(&addr)->sin_addr);
			std::cout << "New connection: " << cip << std::endl;
			addClient(newfd, cip);
			send(newfd, "Please enter a nickname\n", 25, 0);
		}
		if (_fd[0].revents & (POLLERR | POLLHUP | POLLNVAL))
			return (-1);
	}
	return (pollout);
}

bool	Server::addFileDesc(int fd) {
	t_fd pollfd;
	if (fd < 0)
		return (false);
	fcntl(fd, F_SETFL, O_NONBLOCK);				
	pollfd.fd = fd;
	pollfd.events = POLLIN | POLLOUT;
	_fd.push_back(pollfd);
	return (true);
}

void	Server::addClient(int fd, t_str ip) {
	t_client	cli;
	cli.fd = fd;
	cli.ip = ip;
	memset(cli.nick, '\0', 16);
	cli.reg = false;
	_cmap[fd] = cli;
}

void	Server::sendToAllExcept(t_str message, int fd) {
	for (unsigned int i = 1; i < _fd.size(); i++) {
		if (_fd[i].fd != fd) {
			std::stringstream	mout;
			mout << _cmap[fd].nick << ": " << message << '\n';
			send(_fd[i].fd, mout.str().c_str(), mout.str().length(), 0);
		}
	}
}

const char*	Server::socketFailedError::what() const throw() {
	return ("Socket failed");
}

const char*	Server::connectionError::what() const throw() {
	return ("Connection error");
}
