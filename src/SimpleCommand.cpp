#include <SimpleCommand.hpp>

template<class Receiver>
SimpleCommand<Receiver>::SimpleCommand(Receiver *receiver, SimpleCommand::Action action)
: _receiver(receiver), _action(action) {

}

template<class Receiver>
void	SimpleCommand<Receiver>::execute( ) {

	(_receiver->*_action)();
}
