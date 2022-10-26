#ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <cstring>
# include <vector>
# include <exception>

typedef	std::string			t_str;
typedef unsigned short		t_port;
typedef struct sockaddr_in	t_addrin;
typedef struct sockaddr		t_addr;
typedef struct pollfd		t_fd;
typedef std::vector<t_fd>	t_fdv;

class Server {
private:
	t_port	_port;
	t_str	_passwd;
	bool	_ready;
	t_fdv	_fd;
	Server(const Server& x);
	Server&	operator=(const Server& x);
public:
	Server(t_port port = 6667, t_str passwd = "");
	~Server();
	bool	openSocket(t_port port, t_str passwd = "");
	int		pollClients();
	bool	addFileDesc(int fd);
	void	sendToAllExcept(t_str message, int fd);
	class 	socketFailedError : public std::exception {
		virtual const char*	what() const throw();
	};
	class 	connectionError : public std::exception {
		virtual const char*	what() const throw();
	};
};

#endif
