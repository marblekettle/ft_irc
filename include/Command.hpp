#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Types.hpp"
# include <sstream>

class Server;

class	Command
{
	
	protected:

		Server*			_server;

	public:
		explicit		Command(Server *server) : _server(server) {};
		virtual			~Command() {};
		virtual void	execute(std::vector<std::string>& arguments, Client* client) = 0;
		// void			addToQueue( std::queue<Command *> & queue );


};

class JoinCommand : public Command
{
	private:

	public:
		JoinCommand(Server* server);
		~JoinCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class PrivMsgCommand : public Command
{
	private:

	public:
		PrivMsgCommand(Server* server);
		~PrivMsgCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class KickCommand : public Command
{
	private:

	public:
		KickCommand(Server* server);
		~KickCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class QuitCommand : public Command
{
	private:

	public:
		QuitCommand(Server* server);
		~QuitCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class ModeCommand : public Command
{
	private:

	public:
		ModeCommand(Server* server);
		~ModeCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class NickCommand : public Command
{
	private:

	public:
		NickCommand(Server* server);
		~NickCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class UserCommand : public Command
{
	private:

	public:
		UserCommand(Server* server);
		~UserCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class PassCommand : public Command
{
	private:

	public:
		PassCommand(Server* server);
		~PassCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

class PingCommand : public Command
{
	private:

	public:
		PingCommand(Server* server);
		~PingCommand();
		void	execute(std::vector<std::string>& arguments, Client* client);
};

# include "Channel.hpp"

#endif /* COMMAND_HPP */
