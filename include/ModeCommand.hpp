#ifndef FT_IRC_MODECOMMAND_HPP
# define FT_IRC_MODECOMMAND_HPP
# include "Command.hpp"

class ModeCommand : public Command {
private:

public:
	ModeCommand(Server* server);
	~ModeCommand();
	void	execute(std::vector<t_str>& arguments, Client* client);
};

#endif
