#include "ModeCommand.hpp"
#include "Server.hpp"

ModeCommand::ModeCommand(Server* server): Command(server) {}

ModeCommand::~ModeCommand() {}

void	ModeCommand::execute(std::vector<t_str>& arguments, Client* client) {
	if (arguments[1][0] == '#') {
		Channel* ch = _server->getChannel(arguments[1]);
		if (ch == NULL) {
			// ERROR MESSAGE INDICATING CHANNEL DOESNT EXIST
			return ;
		}
		
	} else {
		Client* cl = _server->getClient(arguments[1]);
		if (cl == NULL) {
			// ERROR MESSAGE INDICATING USER DOESNT EXIST
			return ;
		}
	}
}