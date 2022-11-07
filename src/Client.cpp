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

void	Client::sendMessage( Client *sender, std::string message ) {

	std::cout << "sendMessage (from: " << sender->getNick() << ") : " << message << std::endl;
	// TODO implement sending
	_commandQueue.pop();
}

Command *	Client::getNextCommand( ) {

	if (_commandQueue.empty())
		return NULL;
	return _commandQueue.front(); // TODO pop cmd only after success!? (ACK)
}

void	Client::addCommandToQueue( Command * command ) {

	_commandQueue.push(command);
}

/*
** --------------------------------- MUTATORS ---------------------------------
*/

void	Client::setNick(std::string const & nick)
{
	this->_nickname = nick;
}

void	Client::setUser(std::string const & user)
{
	this->_username = user;
}

void	Client::setBuffer(std::string const & buf)
{
	this->_buffer = buf;
}

void	Client::clearBuffer()
{
	this->_buffer.clear();
}

void	Client::appendBuffer(std::string const & buf)
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
