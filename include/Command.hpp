#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <queue>
# include <iostream>
# include <sstream>
# include "Server.hpp"


class	Command
{
	
	protected:

		Server*			_server;

	public:
		explicit		Command(Server *server) : _server(server) {};
		virtual			~Command() {};

		virtual void	execute(std::vector<std::string> arguments) = 0;
		// void			addToQueue( std::queue<Command *> & queue );


};

class JoinCommand : virtual public Command
{
	private:

	public:
		JoinCommand(Server* server);
		~JoinCommand();
		void	execute(std::vector<std::string> arguments);
};

class PrivMsgCommand : public Command
{
	private:

	public:
		PrivMsgCommand(Server* server);
		~PrivMsgCommand();
		void	execute(std::vector<std::string> arguments);
};

class KickCommand : public Command
{
	private:

	public:
		KickCommand(Server* server);
		~KickCommand();
		void	execute(std::vector<std::string> arguments);
};

class QuitCommand : public Command
{
	private:

	public:
		QuitCommand(Server* server);
		~QuitCommand();
		void	execute(std::vector<std::string> arguments);
};

class ModeCommand : public Command
{
	private:

	public:
		ModeCommand(Server* server);
		~ModeCommand();
		void	execute(std::vector<std::string> arguments);
};

#endif /* COMMAND_HPP */
