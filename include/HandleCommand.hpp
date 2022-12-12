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
		std::vector<t_str>				_args;

	public:

		HandleCommand(Server* server);
		~HandleCommand();
		void	call(std::string &message, Client* client);

		size_t	getNArgs() const;
		t_str	getArg(size_t n) const;
};

#endif /* HANDLECOMMAND_HPP */
