#ifndef FT_IRC_MESSAGE_COMMAND_HPP
#define FT_IRC_MESSAGE_COMMAND_HPP

template<typename Receiver>
class SendMessageCommand : public Command {

public:
					SendMessageCommand(Client * sender, Receiver receiver, std::string message );

	virtual void	execute( );

protected:

private:

	Client *		_sender;
	Receiver		_receiver;
	std::string		_message;

};

#endif
