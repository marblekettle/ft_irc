#ifndef HANDLECOMMAND_HPP
#define HANDLECOMMAND_HPP

# include <iostream>
# include <map>
# include <vector>
# include "Server.hpp"
class Client;
class Command;
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
