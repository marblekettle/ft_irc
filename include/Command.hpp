#ifndef FT_IRC_COMMAND_HPP
# define FT_IRC_COMMAND_HPP

class	Command {

public:
	virtual			~Command( ) {}

	virtual void	execute() = 0;

protected:
					Command( ) {}

};

#endif //FT_IRC_COMMAND_HPP