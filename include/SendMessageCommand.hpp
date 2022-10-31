#ifndef FT_IRC_SEND_MESSAGE_COMMAND_HPP
#define FT_IRC_SEND_MESSAGE_COMMAND_HPP

# include <Command.hpp>
# include <Client.hpp>

template<class Receiver>
class SendMessageCommand : public Command {

public:
					SendMessageCommand(Client * sender, Receiver * receiver, std::string message );

	virtual void	execute( );

protected:

private:

	Client *		_client;
	Receiver *		_receiver;
	std::string		_message;

};

#endif //FT_IRC_JOIN_COMMAND_HPP
