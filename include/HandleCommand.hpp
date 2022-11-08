#ifndef HANDLECOMMAND_HPP
#define HANDLECOMMAND_HPP

# include <iostream>
# include <map>
# include "Client.hpp"
# include "Command.hpp"

class HandleCommand
{
	private:

		std::map<std::string, Command*> _commands;

	public:

		HandleCommand();
		~HandleCommand();
		void	call(std::string &message, Client* client);
};

#endif /* HANDLECOMMAND_HPP */
