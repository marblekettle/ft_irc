#include "Channel.hpp"
#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel(const std::string &name, Client *admin) :
	_name(name),
	_password(""),
	_l(-1)
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
	/* remove from client list */
	it = std::find(_clientList.begin(), _clientList.end(), client);
	if (it == _clientList.end())
		return ;
	std::remove(_clientList.begin(), _clientList.end(), client);
	/* remove from admin list */
	it = std::find(_admins.begin(), _admins.end(), client);
	if (it == _admins.end())
		return ;
	std::remove(_admins.begin(), _admins.end(), client);
}

void	Channel::removeAdmin(Client* admin)
{
	std::vector<Client *>::iterator it;

	/* remove from admin list */
	it = std::find(_admins.begin(), _admins.end(), admin);
	if (it == _admins.end())
		return ;
	std::remove(_admins.begin(), _admins.end(), admin);
}

void	Channel::broadCast(std::string message, Client *sender)
{
	std::vector<Client *>::iterator it;
	for (it = _clientList.begin(); it != _clientList.end(); ++it)
	{
		if (*it != sender)
			(*it)->reply(message);
	}
}

void	Channel::broadCast(std::string message)
{
	std::vector<Client *>::iterator it;
	for (it = _clientList.begin(); it != _clientList.end(); ++it)
	{
			(*it)->reply(message);
	}
}

bool	Channel::inClientList(Client* client)
{
	std::vector<Client *>::iterator it;
	for (it = _clientList.begin(); it != _clientList.end(); ++it)
	{
		if (*it == client)
			return (true);
	}
	return (false);
}

bool	Channel::isAdmin(Client* client)
{
	std::vector<Client *>::iterator it;
	for (it = _admins.begin(); it != _admins.end(); ++it)
	{
		if (*it == client)
			return (true);
	}
	return (false);
}

/*
** --------------------------------- COMMANDS ---------------------------------
*/

void	Channel::addClient(Client* new_client)
{
	std::vector<Client *>::iterator it;

	it = std::find(_clientList.begin(), _clientList.end(), new_client);
	if (it != _clientList.end())
		return ; // error: client already in vector
	this->_clientList.push_back(new_client);
}

void	Channel::addAdmin(Client* admin)
{
	std::vector<Client *>::iterator it;

	it = std::find(_admins.begin(), _admins.end(), admin);
	if (it != _admins.end())
		return ; // error: client already in vector
	this->_admins.push_back(admin);
}

std::vector<Client *> &	Channel::getClientList( )
{
	return _clientList;
}

/*
** --------------------------------- MUTATORS ---------------------------------
*/

void		Channel::setPassword(std::string &password)
{
	this->_password = password;
}

void		Channel::setLimit(int const limit)
{
	this->_l = limit;
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

Client*		Channel::getClient(std::string nickname)
{
	std::vector<Client *>::iterator it;
	for (it = _clientList.begin(); it != _clientList.end(); ++it)
	{
		if ((*it)->getNick() == nickname)
			return (*it);
	}
	return (nullptr);
}

int 		Channel::getLimit() const
{
	if (this->_l < 0)
		return (INT_MAX);
	return (this->_l);
}

/* ************************************************************************** */
