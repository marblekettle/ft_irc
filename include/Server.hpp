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
# include "ClientAttr.hpp"
# include <netdb.h>
# include <vector>

class Server {
	private:
		int			_socket;
		t_port		_port;		//Port number
		t_str		_passwd;	//Password
		bool		_ready;		//Polling may NEVER occur unless this is true
		t_fdv		_fd;		//Vector of pollfd structs for polling
		t_addrmap	_addrmap;	//Lookup for struct sockaddr_in
		t_connq		_connq;		//Queue of connections
		t_dataq		_dataq;		//Queue of data
		void	__queue(int fd, t_str data);	//Adds data to the queue

		std::map<int, ClientAttr*>	_clients;
	public:
		Server(t_port port = 6667, t_str passwd = "");
		~Server();
		int		openSocket();					//Change port and password of server
												//	Return: Socket successfully created or not
		void	run();							//Check for all file descriptors if data is available or connection dropped
												//	Return: Number of connections that returned data (i.e. return value of poll())
		bool	connectClient();				//Called when a connection is opened
		void	disconnectClient(int fd);		//Remove a specific file descriptor (e.g. when KILL is called)
		int		getConnections(t_conn& conn);	//Get connection status from queue of new connections (placed inside reference)
												//	Return: Queued connections before calling
		int		getQueuedData(t_datap& data);	//Get data from queue (placed inside reference)
												//	Return: Queued data packets before calling
		t_str	getIP(int fd);					//Get IPv4 address of a specific file descriptor as a string (format X.X.X.X)

		void	clientMessage(int fd);
		void	broadcast(int fd, std::string message);
		t_str	readMessage(int fd);
		class 	socketFailedError : public std::exception {
			virtual const char*	what() const throw();
		};
		class 	connectionError : public std::exception {
			virtual const char*	what() const throw();
		};
};

#endif