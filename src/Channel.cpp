#include "Channel.hpp"
#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(const std::string &name, Client *admin) :
	_name(name),
	_password("")
{
	this->_admins.push_back(admin);
	this->_clientList.push_back(admin);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
	this->_clientList.clear();
	this->_admins.clear();
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Channel &				Channel::operator=( Channel const & rhs )
// /* {
// 	//if ( this != &rhs )
// 	//{
// 		//this->_value = rhs.getValue();
// 	//}
// 	return *this;
// } */

/* std::ostream &			operator<<( std::ostream & o, Channel const & i )
{
	//o << "Value = " << i.getValue();
	return o;
} */


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Channel::removeClient(Client* client)
{
	std::vector<Client *>::iterator it;

	it = std::find(_clientList.begin(), _clientList.end(), client);
	if (it == _clientList.end())
		return ; // error: client not in vector
	std::remove(_clientList.begin(), _clientList.end(), client);
}

/*
** --------------------------------- COMMANDS ---------------------------------
*/

void	Channel::join(Client * new_client)
{
	std::vector<Client *>::iterator it;

	it = std::find(_clientList.begin(), _clientList.end(), new_client);
	if (it != _clientList.end())
		return ; // error: client already in vector
	this->_clientList.push_back(new_client);
	// TODO implementation (iterate to client->list ->add commands(join channel update) to all clients queues
}

std::vector<Client *> &	Channel::getClientList( )
{
	return _clientList;
}

/*
** --------------------------------- MUTATORS ---------------------------------
*/

void		Channel::setPassword(std::string &password, Client* client)
{
	if (std::find(_admins.begin(), _admins.end(), client) != _admins.end())
		this->_password = password;
	/* return error client is not admin */
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string		Channel::getPassword() const
{
	if (_password.size() > 0)
		return (this->_password);
	return ("");
}

std::string		Channel::getName() const
{
	return (this->_name);
}

/* ************************************************************************** */
