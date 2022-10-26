#ifndef FT_IRC_JOIN_COMMAND_HPP
# define FT_IRC_JOIN_COMMAND_HPP

# include <Command.hpp>
# include <Client.hpp>

template<class Receiver>
class JoinCommand : public Command {

public:
					JoinCommand( Client * client, Receiver * receiver );

	virtual void	execute( );

protected:

private:

	Client *		_client;
	Receiver *		_receiver;

};

#endif //FT_IRC_JOIN_COMMAND_HPP
