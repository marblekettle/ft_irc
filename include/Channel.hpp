#ifndef FT_IRC_CHANNEL_HPP
# define FT_IRC_CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>

class Client;

class Channel
{
	private:

		const std::string			_name;
		std::vector<Client*>		_admins;
		std::vector<Client*>		_clientList;
		std::string					_password;

	public:

		Channel(const std::string &name, Client *admin);
		~Channel();

		std::string				getPassword() const;
		std::string				getName() const;
		std::vector<Client *> &	getClientList();
		Client*					getClient(std::string nickname);

		bool					inClientList(Client* client);
		bool					isAdmin(Client* client);

		void					broadCast(std::string message, Client* sender);
		void					broadCast(std::string message);
		void					removeClient(Client* client);
		void					addClient(Client* new_client);
		void					setPassword(std::string &password);


};

// std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */
