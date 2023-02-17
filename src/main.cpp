#include "Server.hpp"
#include "utils.hpp"

Server*	g_server = NULL;

void	sig_stop(int code) {
	if (code == SIGINT && g_server)
		g_server->stop();
}

int		main(int ac, char** av) {
	if (ac == 3) 
	{
		t_str	portstr(av[1]);
		t_str	passwd(av[2]);
		if (portstr.find_first_not_of("123467890") != std::string::npos) {
			std::cerr << "Incorrect port number" << std::endl;
			return (0);
		}
		t_port	port = static_cast<t_port>(std::stoi(portstr));
		try {
			Server	server(port, passwd);
			g_server = &server;
			signal(SIGINT, sig_stop);
			server.run();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	} 
	else 
	{
		std::cerr << "Incorrect arguments" << std::endl;
	}
	std::cerr << strerror(errno) << std::endl;
	return (0);
}
