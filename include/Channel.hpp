#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "ClientAttr.hpp"
# include <vector>

class Channel
{

	private:

		const std::string			_name;
		ClientAttr*					_admin;
		std::vector<ClientAttr *>	_clients;
		std::string					_password;

	public:

		Channel(const std::string &name, const std::string &password, ClientAttr *admin);
		~Channel();

		std::string		getPassword() const;
		std::string		getName() const;
		ClientAttr*		getAdmin() const;
		void			addClient(ClientAttr *new_client);
		void			removeClient(ClientAttr *client);
		void			setPassword(std::string &password);

};

// std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */
