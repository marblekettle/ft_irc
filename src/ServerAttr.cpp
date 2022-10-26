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

ClientAttr&		ServerAttr::getClient(std::string username) const
{
	return (this->_clients.find(username));
}

/* ************************************************************************** */