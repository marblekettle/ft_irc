#ifndef SERVER_HPP
# define SERVER_HPP
# include <sys/socket.h>
# include <arpa/inet.h>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <cstring>
# include <exception>
# include "Types.hpp"

class Server {
private:
	t_port		_port;
	t_str		_passwd;
	bool		_ready;
	t_fdv		_fd;
	t_addrmap	_addrmap;
	t_connq		_connq;
	t_dataq		_dataq;
	Server(const Server& x);
	Server&	operator=(const Server& x);
	bool	__addclient();
	void	__queue(int fd, t_str data);
public:
	Server(t_port port = 6667, t_str passwd = "");
	~Server();
	bool	openSocket(t_port port, t_str passwd = "");
	int		pollClients();
	void	disconnectClient(int fd);
	int		getConnections(t_conn& conn);
	int		getQueuedData(t_datap& data);
	t_str	getIP(int fd);
	class 	socketFailedError : public std::exception {
		virtual const char*	what() const throw();
	};
	class 	connectionError : public std::exception {
		virtual const char*	what() const throw();
	};
};

#endif