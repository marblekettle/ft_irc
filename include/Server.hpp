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
	t_port	_port;
	t_str	_passwd;
	bool	_ready;
	t_fdv	_fd;
	t_cmap	_cmap;
	Server(const Server& x);
	Server&	operator=(const Server& x);
public:
	Server(t_port port = 6667, t_str passwd = "");
	~Server();
	bool	openSocket(t_port port, t_str passwd = "");
	int		pollClients();
	bool	addFileDesc(int fd);
	void	addClient(int fd, t_str ip);
	void	sendToAllExcept(t_str message, int fd);
	class 	socketFailedError : public std::exception {
		virtual const char*	what() const throw();
	};
	class 	connectionError : public std::exception {
		virtual const char*	what() const throw();
	};
};

#endif