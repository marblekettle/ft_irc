#ifndef SERVERATTR_HPP
# define SERVERATTR_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include "ClientAttr.hpp"

class ServerAttr
{

	private:

		uint32_t					_port;
		std::string					_password;
		// std::string					_host;
		std::map<std::string, ClientAttr*>	_clients;

		ServerAttr();

	public:

		ServerAttr(std::string& port, std::string& password);
		ServerAttr( ServerAttr const & src );
		~ServerAttr();

		ServerAttr &		operator=( ServerAttr const & rhs );
		// std::string			getHost() const;
		std::string			getPassword() const;
		uint32_t			getPort() const;
		ClientAttr&			getClient(std::string username) const;

};

std::ostream &			operator<<( std::ostream & o, ServerAttr const & i );

#endif /* ****************************************************** SERVERATTR_H */
