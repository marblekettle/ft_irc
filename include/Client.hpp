#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <Command.hpp>
# include <iostream>
# include <string>
# include <queue>

# define INIT_BUFFER 100

class Client
{
	private:

		const int 				_fd;
		std::string				_nickname;
		std::string				_username;
		std::string				_buffer;
		std::queue<Command *>	_commandQueue;

		Client();

	public:

							Client(int const fd);
							Client(Client const & src);
		Client &			operator=( Client const & rhs );
							~Client();


		int					getFd();
		std::string			getNick() const;
		std::string			getUser() const;
		std::string			getBuffer() const;

		void				setNick(std::string const & nick);
		void				setUser(std::string const & user);
		void				setBuffer(std::string const & user);
		void				appendBuffer(std::string const & user);
		void				clearBuffer();

		void				sendMessage(Client * sender, std::string message);
		Command *			getNextCommand();
		void				addCommandToQueue( Command * command );
};

std::ostream &			operator<<( std::ostream& o, Client const& i );

#endif /* ****************************************************** CLIENT_H */
