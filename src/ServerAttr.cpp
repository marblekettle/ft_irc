#include "ServerAttr.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerAttr::ServerAttr() {}

ServerAttr::ServerAttr(std::string& port, std::string& password)
{
	this->_port = atoi(port.c_str());
	this->_password = password;
}

ServerAttr::ServerAttr( const ServerAttr & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerAttr::~ServerAttr()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerAttr &				ServerAttr::operator=( ServerAttr const & rhs )
{
	if ( this != &rhs )
	{
		this->_port = rhs.getPort();
		this->_password = rhs.getPassword();
		this->_clients = rhs._clients;
	}
	return (*this);
}

// std::ostream &			operator<<( std::ostream & o, ServerAttr const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- MUTATORS ---------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string		ServerAttr::getPassword() const
{
	return (this->_password);
}

uint32_t	ServerAttr::getPort() const
{
	return (this->_port);
}

Client*		ServerAttr::getClient(std::string& username) const
{
	std::map<std::string, Client*>::const_iterator it;

	it = this->_clients.find(username);
	if (it != this->_clients.end())
		return (it->second);
	
	return (nullptr);
}

/* ************************************************************************** */
