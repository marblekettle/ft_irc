#ifndef FT_IRC_CLIENT_HPP
# define FT_IRC_CLIENT_HPP

# include "responses.hpp"
# include <Types.hpp>
# include <iostream>
# include <cstring>
# include <queue>
# include <sstream>
# include <sys/socket.h>
# include "utils.hpp"
# include <cerrno>
# define INIT_BUFFER 100
class Command;
class Channel;
/* The 5 states to get access are
   LOGIN - there is only a connection
   AUTHENTICATED - the password is set and valid
   REGISTERED - a unique NICK is set
   ACCESS - username and realname are set, now the client has access to the server */

enum state
{
	LOGIN,
	AUTHENTICATED,
	REGISTERED,
	ACCESS
};

/* TODO add vector of current channels pointers where the client is in */

typedef std::vector<Channel*>::iterator t_chan_iter; //Iterator for a vector with channel pointers

class Client
{
	private:

		const int 				_fd;
		std::string				_nickname;
		std::string				_username;
		std::string				_realname;
		std::string				_buffer;
		const std::string		_host;
		std::queue<t_str>		_commandQueue;
		int						_state;
		std::vector<Channel *>	_activeChannels;
		std::queue<t_str>		_responseQueue;

		Client();

	public:

		Client(int const fd, const std::string& host);
		~Client();
		void				queueResponse(const t_str& message);
		int					nResponses();
		t_str				popResponse();
		bool				readMessages(t_str& message);

		int					getFd()	const;
		int					getState() const;
		std::string			getNick() const;
		std::string			getUser() const;
		std::string			getHost() const;
		std::string			getRealName() const;
		std::string			getBuffer() const;
		std::string			getPrefix();

		void				setState(int	new_state);
		void				setNick(const std::string& nick);
		void				setUser(const std::string& user);
		void		 		setRealName(const std::string& user);
		void				setBuffer(const std::string& user);
		void				appendBuffer(const std::string& user);
		void				clearBuffer();

		void				addChannel(Channel* channel);
		void				popChannel(Channel* channel);
		void				clearActiveChannels();
		t_chan_iter			getActiveChannelBegin();
		t_chan_iter			getActiveChannelEnd();

		void				welcome();
		void				reply(std::string message);
		void				sendMessage(std::string message);
		void				addCommandToQueue(const t_str& string);
		bool				popCommand(t_str& out);
};

std::ostream &			operator<<( std::ostream& o, Client const& i );

#endif /* ****************************************************** CLIENT_H */
