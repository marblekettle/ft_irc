#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <queue>
# include <sstream>
# include <sys/socket.h>
# include "Server.hpp"
# define INIT_BUFFER 100
class Command;

class Client
{
	private:

		const int 				_fd;
		std::string				_nickname;
		std::string				_username;
		std::string				_realname;
		std::string				_buffer;
		const std::string		_host;
		bool					_isAuthorized;
		std::queue<Command *>	_commandQueue;

	public:

		Client(int const fd, const std::string& host);
		~Client();


		int					getFd();
		std::string			getNick() const;
		std::string			getUser() const;
		std::string			getHost() const;
		std::string			getRealName() const;
		std::string			getBuffer() const;
		std::string			getPrefix();

		void				setNick(std::string& nick);
		void				setUser(std::string& user);
		void				setRealName(std::string& user);
		void				setBuffer(std::string& user);
		void				appendBuffer(std::string& user);
		void				clearBuffer();


		void				sendMessage(std::string message);
		Command *			getNextCommand();
		void				addCommandToQueue( Command * command );
};

std::ostream &			operator<<( std::ostream& o, Client const& i );

#endif /* ****************************************************** CLIENT_H */
