#include "ClientAttr.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ClientAttr::ClientAttr() : _fd(-1) {}

ClientAttr::ClientAttr(int const fd) :
	_fd(fd)
{
	_buffer.resize(INIT_BUFFER);
	return ;
}

ClientAttr::ClientAttr( const ClientAttr & src ) :
	_fd(src._fd)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ClientAttr::~ClientAttr()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ClientAttr &				ClientAttr::operator=( ClientAttr const & rhs )
{
	if ( this != &rhs )
	{
		_nickname = rhs.getNick();
		_username = rhs.getUser();
		_buffer = rhs.getBuffer();
	}
	return (*this);
}

// std::ostream &			operator<<( std::ostream & o, ClientAttr const & i )
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


void	ClientAttr::setNick(std::string& nick)
{
	this->_nickname = nick;
}

void	ClientAttr::setUser(std::string& user)
{
	this->_username = user;
}

void	ClientAttr::setBuffer(std::string& buf)
{
	this->_buffer = buf;
}

void	ClientAttr::clearBuffer()
{
	this->_buffer.clear();
}

void	ClientAttr::appendBuffer(std::string& buf)
{
	this->_buffer += buf;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int		ClientAttr::getFd()
{
	return (this->_fd);
}

std::string	ClientAttr::getNick() const
{
	return (this->_nickname);
}

std::string	ClientAttr::getUser() const
{
	return (this->_username);
}

std::string	ClientAttr::getBuffer() const
{
	return (this->_buffer);
}

size_t	ClientAttr::getBufSize() const
{
	return (this->_buffer.size());
}

/* ************************************************************************** */
