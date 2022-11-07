#include <JoinCommand.hpp>

template<class Receiver>
JoinCommand<Receiver>::JoinCommand( Client * client, Receiver * receiver )
: _client(client), _receiver(receiver) {

}

template<class Receiver>
void	JoinCommand<Receiver>::execute( ) {

	_receiver->join(_client);
}
