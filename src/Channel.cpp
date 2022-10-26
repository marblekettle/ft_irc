#include <Channel.hpp>

Channel::Channel( const std::string & name )
: _name(name), _clientList() {

}


void	Channel::join( Client * client ) {

	_clientList.push_back(client);
}
