#ifndef MESSAGE_COMMAND_HPP
#define MESSAGE_COMMAND_HPP

//# include <Command.hpp>
//# include <Client.hpp>

template<typename Receiver>
class SendMessageCommand : public Command {

public:
					SendMessageCommand(Client * sender, Receiver * receiver, std::string message );

	virtual void	execute( );

protected:

private:

	Client *		_sender;
	Receiver *		_receiver;
	std::string		_message;

};

#endif
