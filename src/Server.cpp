#include "Server.hpp"

bool	Server::__addclient() {
	t_fd	pollfd;
	t_addr	addr;
	std::memset(&addr, 0, sizeof(t_addrin));
	socklen_t	addrlen = sizeof(t_addr);
	pollfd.fd = accept(_fd[0].fd, &addr, &addrlen);
	if (pollfd.fd < 0)
		return (false);
	if (addrlen != sizeof(t_addr)) {
		close (pollfd.fd);
		return (false);
	}
	fcntl(pollfd.fd, F_SETFL, O_NONBLOCK);
	pollfd.events = POLLIN | POLLOUT;
	_fd.push_back(pollfd);
	_addrmap[pollfd.fd] = *(reinterpret_cast<t_addrin*>(&addr));
	t_conn	conn;
	conn.first = pollfd.fd;
	conn.second = true;
	_connq.push(conn);
	return (true);
}

void	Server::__queue(int fd, t_str data) {
	t_datap	datap;
	datap.first = fd;
	datap.second = data;
	_dataq.push(datap);
}

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
				__queue(it->fd, message);
			}
			if (it->revents & (POLLERR | POLLHUP | POLLNVAL)) {
				std::cout << "FD " << it->fd << " disconnected!" << std::endl;
				disconnectClient(it->fd);
				_fd.erase(it);
				it--;
			}
		}
		if (_fd[0].revents & POLLIN) {
			if (!__addclient())
				throw (connectionError());
		}
		if (_fd[0].revents & (POLLERR | POLLHUP | POLLNVAL))
			return (-1);
	}
	return (pollout);
}

void	Server::disconnectClient(int fd) {
	t_conn	conn;
	conn.first = fd;
	conn.second = false;
	_connq.push(conn);
	close(fd);
	_addrmap.erase(fd);
}

int		Server::getConnections(t_conn& conn) {
	int	siz = _connq.size();
	if (siz) {
		conn = _connq.front();
		_connq.pop();
	}
	return (siz);
}

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

const char*	Server::socketFailedError::what() const throw() {
	return ("Socket failed");
}

const char*	Server::connectionError::what() const throw() {
	return ("Connection error");
}
