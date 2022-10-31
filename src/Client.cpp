#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client() : _fd(-1) {}

Client::Client(int const fd) :
	_fd(fd)
{
	_buffer.resize(INIT_BUFFER);
	return ;
}

Client::Client( const Client & src ) :
	_fd(src._fd)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client()
{
	clearBuffer();
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Client &				Client::operator=( Client const & rhs )
{
	if ( this != &rhs )
	{
		_nickname = rhs.getNick();
		_username = rhs.getUser();
		_buffer = rhs.getBuffer();
	}
	return (*this);
}

// std::ostream &			operator<<( std::ostream & o, Client const & i )
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


void	Client::setNick(std::string& nick)
{
	this->_nickname = nick;
}

void	Client::setUser(std::string& user)
{
	this->_username = user;
}

void	Client::setBuffer(std::string& buf)
{
	this->_buffer = buf;
}

void	Client::clearBuffer()
{
	this->_buffer.clear();
}

void	Client::appendBuffer(std::string& buf)
{
	this->_buffer += buf;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int		Client::getFd()
{
	return (this->_fd);
}

std::string	Client::getNick() const
{
	return (this->_nickname);
}

std::string	Client::getUser() const
{
	return (this->_username);
}

std::string	Client::getBuffer() const
{
	return (this->_buffer);
}

/* ************************************************************************** */
