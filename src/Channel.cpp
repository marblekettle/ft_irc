#include "Channel.hpp"
#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(const std::string &name, const std::string &password, Client *admin) :
	_name(name),
	_admin(admin),
	_password(password)
{
	this->_clientList.push_back(admin);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
	this->_clientList.clear();
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

std::vector<Client *> &	Channel::getClientList( ) {

	return _clientList;
}

/*
** --------------------------------- MUTATORS ---------------------------------
*/

void		Channel::setPassword(std::string &password)
{
	this->_password = password;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string		Channel::getPassword() const
{
	return (this->_password);
}

std::string		Channel::getName() const
{
	return (this->_name);
}

Client*		Channel::getAdmin() const
{
	return (this->_admin);
}

/* ************************************************************************** */
