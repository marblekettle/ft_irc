#ifndef FT_IRC_SIMPLE_COMMAND_HPP
# define FT_IRC_SIMPLE_COMMAND_HPP

# include <iostream>

template<class Receiver>
class SimpleCommand : public Command {

public:

	typedef void	(Receiver::* Action)();

					SimpleCommand(Receiver * receiver, Action action);

	virtual void	execute( );

protected:

private:

	Receiver *		_receiver;
	Action			_action;
};

#endif //FT_IRC_SIMPLECOMMAND_HPP
