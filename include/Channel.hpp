#ifndef FT_IRC_CHANNEL_HPP
# define FT_IRC_CHANNEL_HPP

# include "Types.hpp"

class Channel
{
	private:

		const std::string			_name;
		std::vector<Client*>		_admins;
		std::vector<Client*>		_clientList;
		std::string					_password;
		int							_l;

	public:

		Channel(const std::string &name, Client *admin);
		~Channel();

		int						getLimit() const;
		std::string				getPassword() const;
		std::string				getName() const;
		std::vector<Client *> &	getClientList();
		Client*					getClient(std::string nickname);

		bool					inClientList(Client* client);
		bool					isAdmin(Client* client);

		void					broadCast(std::string message, Client* sender);
		void					broadCast(std::string message);
		void					removeClient(Client* client);
		void					removeAdmin(Client* admin);
		void					addClient(Client* new_client);
		void					addAdmin(Client* admin);
		void					setPassword(std::string &password);
		void					setLimit(int const limit);


};

// std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */
