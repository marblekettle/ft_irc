#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <queue>
# include <iostream>
# include <sstream>

class	Command {

public:
					Command( ) {};
	virtual			~Command( ) {};

	virtual void	execute() = 0;
	void			addToQueue( std::queue<Command *> & queue );

protected:

};

class JoinCommand : public Command
{
	private:

	public:
		JoinCommand();
		~JoinCommand();
		void	execute();
};
class PrivMsgCommand : public Command
{
	private:

	public:
		PrivMsgCommand();
		~PrivMsgCommand();
		void	execute();
};
class KickCommand : public Command
{
	private:

	public:
		KickCommand();
		~KickCommand();
		void	execute();
};
class QuitCommand : public Command
{
	private:

	public:
		QuitCommand();
		~QuitCommand();
		void	execute();
};
class ModeCommand : public Command
{
	private:

	public:
		ModeCommand();
		~ModeCommand();
		void	execute();
};




#endif /* COMMAND_HPP */
