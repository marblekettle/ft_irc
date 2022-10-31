#ifndef CLIENT_HPP
# define CLIENT_HPP

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
		std::queue<std::string>	_msg;

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


		void				setNick(std::string& nick);
		void				setUser(std::string& user);
		void				setBuffer(std::string& user);
		void				appendBuffer(std::string& user);
		void				clearBuffer();
};

std::ostream &			operator<<( std::ostream& o, Client const& i );

#endif /* ****************************************************** CLIENT_H */
