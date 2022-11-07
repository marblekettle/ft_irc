#ifndef SERVERATTR_HPP
# define SERVERATTR_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <map>
# include <vector>
# include "Client.hpp"

class ServerAttr
{

	private:

		// std::string					_host;
		uint32_t					_port;
		std::string					_password;
		std::map<int, Client*>		_clients;

		ServerAttr();

	public:

										ServerAttr(std::string& port, std::string& password);
										ServerAttr( ServerAttr const & src );
										~ServerAttr();
		ServerAttr &					operator=( ServerAttr const & rhs );

		// std::string					getHost() const;
		std::string						getPassword() const;
		uint32_t						getPort() const;
		Client*							getClient(std::string& username) const;

};

std::ostream &			operator<<( std::ostream & o, ServerAttr const & i );

#endif /* ****************************************************** SERVERATTR_H */



