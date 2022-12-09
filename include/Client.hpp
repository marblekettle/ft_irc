#ifndef FT_IRC_CLIENT_HPP
# define FT_IRC_CLIENT_HPP

# include "responses.hpp"
# include <Types.hpp>
# include <iostream>
# include <string>
# include <queue>
# include <sstream>
# include <sys/socket.h>
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

//	____Experimental____

		std::queue<t_str>		_responseQueue;

//	____________________

		Client();

	public:

		Client(int const fd, const std::string& host);
		~Client();

//	____Experimental____

		void				queueResponse(const t_str& message);
		int					nResponses();
		t_str				popResponse();

//	____________________

		int					getFd();
		std::string			getNick() const;
		std::string			getUser() const;
		std::string			getHost() const;
		std::string			getRealName() const;
		std::string			getBuffer() const;
		std::string			getPrefix();

		void				setNick(const std::string& nick);
		void				setUser(const std::string& user);
		void				setRealName(const std::string& user);
		void				setBuffer(const std::string& user);
		void				appendBuffer(const std::string& user);
		void				clearBuffer();

		void				welcome();
		void				reply(std::string message);
		void				sendMessage(std::string message);
		Command *			getNextCommand();
		void				addCommandToQueue( Command * command );
};

std::ostream &			operator<<( std::ostream& o, Client const& i );

#endif /* ****************************************************** CLIENT_H */
