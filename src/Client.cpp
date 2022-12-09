#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(int const fd, const std::string& host) :
	_fd(fd),
	_host(host),
	_isAuthorized(false)
{
	_buffer.resize(INIT_BUFFER);
	return ;
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


// std::ostream &			operator<<( std::ostream & o, Client const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Client::sendMessage(std::string message ) {

	std::stringstream ss;
	ss << ":" << getPrefix() << " " << message << "\r\n";
	send(_fd, ss.str().c_str(), ss.str().length(), 0);
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

void	Client::setNick(std::string& nick)
{
	this->_nickname = nick;
}

void	Client::setUser(std::string& user)
{
	this->_username = user;
}

void	Client::setRealName(std::string& name)
{
	this->_realname = name;
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

std::string	Client::getHost() const
{
	return (this->_host);
}

std::string	Client::getUser() const
{
	return (this->_username);
}

std::string	Client::getRealName() const
{
	return (this->_realname);
}

std::string	Client::getBuffer() const
{
	return (this->_buffer);
}

std::string	Client::getPrefix()
{
	if (_isAuthorized)
	{
		std::stringstream	prefix;

		prefix << getNick() << "!" << getUser() << "@" << getHost();
		return (prefix.str());
	}
	return ("");
}

/* ************************************************************************** */
