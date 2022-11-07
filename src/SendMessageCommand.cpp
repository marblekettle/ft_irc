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

	std::cout << "SendMessageCommand(Client): " << _message << std::endl;
	reinterpret_cast<Client *>(_receiver)->sendMessage(_sender, _message);
}

template<>
void	SendMessageCommand<Channel *>::execute( ) {

	std::cout << "SendMessageCommand(Channel): " << _message << std::endl;
	std::vector<Client *> & clientList = reinterpret_cast<Channel *>(_receiver)->getClientList();
	for (std::vector<Client *>::iterator it = clientList.begin(); it <= clientList.end(); it++)
	{
		(*it)->addCommandToQueue(new SendMessageCommand<Client *>(_sender, &(*it), _message));
	}
}
