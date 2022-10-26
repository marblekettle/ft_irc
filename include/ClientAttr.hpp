#ifndef CLIENTATTR_HPP
# define CLIENTATTR_HPP

# include <iostream>
# include <string>

# define INIT_BUFFER 100

class ClientAttr
{
	private:

		const int 		_fd;
		std::string		_nickname;
		std::string		_username;
		std::string		_buffer;

		ClientAttr();

	public:

		ClientAttr(int const fd);
		ClientAttr(ClientAttr const & src);
		ClientAttr &		operator=( ClientAttr const & rhs );
		~ClientAttr();


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

std::ostream &			operator<<( std::ostream& o, ClientAttr const& i );

#endif /* ****************************************************** CLIENTATTR_H */
