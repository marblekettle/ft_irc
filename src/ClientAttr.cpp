#include "ClientAttr.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ClientAttr::ClientAttr() : _fd(-1) {}

ClientAttr::ClientAttr(int const fd) :
	_fd(fd)
{
	buffer.resize(INIT_BUFFER);
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
		nickname = rhs.getNick();
		username = rhs.getUser();
		buffer = rhs.getBuffer();
	}
	return (*this);
}

std::ostream &			operator<<( std::ostream & o, ClientAttr const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/



/*
** --------------------------------- MUTATORS ---------------------------------
*/


void	ClientAttr::setNick(std::string& const nick)
{
	this->nickname = nick;
}

void	ClientAttr::setUser(std::string& const user)
{
	this->username = user;
}

void	ClientAttr::setBuffer(std::string& const buf)
{
	this->buffer = buf;
}

void	ClientAttr::clearBuffer()
{
	this->buffer.clear();
}

void	ClientAttr::appendBuffer(std::string& const buf)
{
	this->buffer += buf;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int const		ClientAttr::getFd()
{
	return (this->_fd);
}

const std::string&	ClientAttr::getNick() const
{
	return (this->nickname);
}

const std::string&	ClientAttr::getNick() const
{
	return (this->nickname);
}

const std::string&	ClientAttr::getBuffer() const
{
	return (this->buffer);
}

size_t const	ClientAttr::getBufSize() const
{
	return (this->buffer.size());
}

/* ************************************************************************** */
