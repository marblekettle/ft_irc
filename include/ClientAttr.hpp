#ifndef CLIENTATTR_HPP
# define CLIENTATTR_HPP

# include <iostream>
# include <string>

# define INIT_BUFFER 100

class ClientAttr
{
	private:

		const int 		_fd;
		std::string		nickname;
		std::string		username;
		std::string		buffer;

		ClientAttr();

	public:

		ClientAttr(int const fd);
		ClientAttr(ClientAttr const & src);
		ClientAttr &		operator=( ClientAttr const & rhs );
		~ClientAttr();


		const int				getFd();
		const std::string&		getNick() const;
		const std::string&		getUser() const;
		const std::string&		getBuffer() const;
		const size_t			getBufSize() const;
		void					setNick(std::string& const nick);
		void					setUser(std::string& const user);
		void					setBuffer(std::string& const user);
		void					appendBuffer(std::string& const user);
		void					clearBuffer();
};

std::ostream &			operator<<( std::ostream& o, ClientAttr const& i );

#endif /* ****************************************************** CLIENTATTR_H */
