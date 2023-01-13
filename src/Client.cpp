#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client(int const fd, const std::string& host) :
	_fd(fd),
	_host(host),
	_state(LOGIN)
{
	//_buffer.resize(INIT_BUFFER);
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


// std::ostream &			operator+( std::ostream & o, Client const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/


void	Client::reply(std::string message) {
	
	std::string buffer;
	buffer = message + "\r\n";
	if (send(_fd, buffer.c_str(), buffer.size(), 0) < 0)
		throw std::runtime_error("Error sending message");
	logToServer(message);
}

void	Client::sendMessage(std::string message ) {

	std::cout << "sendMessage (from: " << this->getNick() << ") : " << message << std::endl;
	// TODO implement sending
	_commandQueue.pop();
}

/*
Command *	Client::getNextCommand( ) {

	if (_commandQueue.empty())
		return NULL;
	return _commandQueue.front(); // TODO pop cmd only after success!? (ACK)
}
*/

void	Client::addCommandToQueue(const t_str& string) {

	_commandQueue.push(string);
}

bool	Client::popCommand(t_str& out) {
	if (_commandQueue.size() == 0) 
		return (false);
	out = _commandQueue.front();
	_commandQueue.pop();
	return (true);
}

bool	Client::readMessages(t_str& message) {
/*	if (_buffer.length() == 0) {
		char	buf[10];
		int		ret = 1;
		while (ret > 0) {
			bzero(buf, 10);
			ret = recv(_fd, buf, 9, 0);
			if (ret < 0)
			{
				if (errno != EWOULDBLOCK)
					throw (std::runtime_error("Error with reading buf from client"));
			}
			_buffer.append(buf);
			std::cerr << _buffer << std::endl;
		}
	}
*/
	char	buf[10];
	while (1) {
		bzero(buf, 10);
		int ret = recv(_fd, buf, 9, 0);
		if (ret < 0)
		{
			if (errno != EWOULDBLOCK)
				throw (std::runtime_error("Error with reading buf from client"));
			break ;
		}
		if (ret == 0)
			break ;
		_buffer.append(buf);
	}
	size_t index = _buffer.find("\r\n");
	if (index == std::string::npos)
		return (false);
	message = _buffer.substr(0, index);
	_buffer = _buffer.substr(index + 2);
	std::cerr << "DEBUG--> " << message << std::endl;
	return (true);
}

void	Client::welcome()
{
	if (_username.empty() || _realname.empty() || _nickname.empty())
		return ;
	_state = ACCESS;
	reply(RPL_WELCOME(_host, _nickname));
}

/*
** --------------------------------- MUTATORS ---------------------------------
*/


void	Client::setState(int new_state)
{
	this->_state = new_state;
}

void	Client::setNick(const std::string& nick)
{
	this->_nickname = nick;
}

void	Client::setUser(const std::string& user)
{
	this->_username = user;
}

void	Client::setRealName(const std::string& name)
{
	this->_realname = name;
}

void	Client::setBuffer(const std::string& buf)
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

int			Client::getFd() const
{
	return (this->_fd);
}

int			Client::getState() const
{
	return (this->_state);
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
	return (":" + _nickname + (_username.empty() ? "" : "!" + _username) + (_host.empty() ? "" : "@" + _host));
}

/* ************************************************************************** */

//	____Experimental____

void	Client::queueResponse(const t_str& message) {
	_responseQueue.push(message);
}

int		Client::nResponses() {
	return (_responseQueue.size());
}

t_str	Client::popResponse() {
	t_str	response = _responseQueue.front();
	_responseQueue.pop();
	return (response);
}

//	____________________
