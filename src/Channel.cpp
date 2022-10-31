#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(const std::string &name, const std::string &password, Client *admin) :
	_name(name),
	_admin(admin),
	_password(password)
{
	this->_clients.push_back(admin);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
	this->_clients.clear();
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

void	Channel::addClient(Client* new_client)
{
	std::vector<Client *>::iterator it;

	it = std::find(_clients.begin(), _clients.end(), new_client);
	if (it != _clients.end())
		return ; // error: client already in vector
	this->_clients.push_back(new_client);
}

void	Channel::removeClient(Client* client)
{
	std::vector<Client *>::iterator it;

	it = std::find(_clients.begin(), _clients.end(), client);
	if (it == _clients.end())
		return ; // error: client not in vector
	std::remove(_clients.begin(), _clients.end(), client);
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
