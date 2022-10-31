#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>
# include <Client.hpp>

class Channel
{

	private:

		const std::string			_name;
		Client 						_admin;
		std::vector<Client*>		_clientList;
		std::string					_password;

	public:

		Channel(const std::string &name, const std::string &password, Client *admin);
		~Channel();

		std::string				getPassword() const;
		std::string				getName() const;
		Client*					getAdmin() const;
		std::vector<Client *> *	getClientList();
		void					removeClient(Client *client);

//		void			sendMessageCommand(Client * sender, std::string message);
		void			join(Client *new_client);

		void			setPassword(std::string &password);

};

// std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */
