#include <Command.hpp>
#include <Channel.hpp>
#include <Client.hpp>
#include <SendMessageCommand.hpp>

template<typename Receiver>
SendMessageCommand<Receiver>::SendMessageCommand(Client * sender, Receiver * receiver, std::string message )
: _sender(sender), _receiver(receiver), _message(message) {

}

template<>
void	SendMessageCommand<Client *>::execute( ) {

	reinterpret_cast<Client *>(_receiver)->sendMessage(_sender, _message);
}

template<>
void	SendMessageCommand<Channel *>::execute( ) {

	for (std::vector<Client *>::iterator it = reinterpret_cast<Channel *>(_receiver)->getClientList()->begin(); it < reinterpret_cast<Channel *>(_receiver)->getClientList()->end(); it++)
	{
		reinterpret_cast<Client *>
	}
	reinterpret_cast<Channel *>(_receiver)->sendMessage(_sender, _message);
}

//template<>
//void	SendMessageCommand<Client *>::execute( ) {
//
//	std::cout << "SendMessageCommand(Client): " << this->_message << std::endl;
//}
//
//template<>
//void	SendMessageCommand<Channel *>::execute( ) {
//
//	std::cout << "SendMessageCommand(Channel): " << this->_message << std::endl;
//}
