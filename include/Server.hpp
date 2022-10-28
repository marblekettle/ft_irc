// Server.hpp : An object to manage connections and datastreams, for outputting data and linking clients to IP addresses and file descriptors

#ifndef SERVER_HPP
# define SERVER_HPP
# include <sys/socket.h>	//socket()
# include <arpa/inet.h>		//htons(), htonl()
# include <poll.h>			//poll(), struct pollfd
# include <fcntl.h>			//fcntl()
# include <unistd.h>		//close()
# include <cstring>			//memset()
# include <exception>		//std::exception
# include "Types.hpp"

class Server {
private:
	t_port		_port;		//Port number
	t_str		_passwd;	//Password
	bool		_ready;		//Polling may NEVER occur unless this is true
	t_fdv		_fd;		//Vector of pollfd structs for polling
	t_addrmap	_addrmap;	//Lookup for struct sockaddr_in
	t_connq		_connq;		//Queue of connections
	t_dataq		_dataq;		//Queue of data
	Server(const Server& x);
	Server&	operator=(const Server& x);
	bool	__addclient();					//Called when a connection is opened
	void	__queue(int fd, t_str data);	//Adds data to the queue
public:
	Server(t_port port = 6667, t_str passwd = "");
	~Server();
	bool	openSocket(t_port port, t_str passwd = "");	//Change port and password of server
											//	Return: Socket successfully created or not
	int		pollClients();					//Check for all file descriptors if data is available or connection dropped
											//	Return: Number of connections that returned data (i.e. return value of poll())
	void	disconnectClient(int fd);		//Remove a specific file descriptor (e.g. when KILL is called)
	int		getConnections(t_conn& conn);	//Get connection status from queue of new connections (placed inside reference)
											//	Return: Queued connections before calling
	int		getQueuedData(t_datap& data);	//Get data from queue (placed inside reference)
											//	Return: Queued data packets before calling
	t_str	getIP(int fd);					//Get IPv4 address of a specific file descriptor as a string (format X.X.X.X)
	class 	socketFailedError : public std::exception {
		virtual const char*	what() const throw();
	};
	class 	connectionError : public std::exception {
		virtual const char*	what() const throw();
	};
};

#endif