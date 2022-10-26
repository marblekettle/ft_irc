#ifndef FT_IRC_SIMPLECOMMAND_HPP
# define FT_IRC_SIMPLECOMMAND_HPP

# include <Command.hpp>

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
