#ifndef HANDLECOMMAND_HPP
#define HANDLECOMMAND_HPP

# include "Command.hpp"
# include "Types.hpp"

class Server;

class HandleCommand
{
	private:

		Server*							_server;
		std::map<std::string, Command*> _commands;

	public:

		HandleCommand(Server* server);
		~HandleCommand();
		void	call(std::string &message, Client* client);
};

#endif /* HANDLECOMMAND_HPP */
