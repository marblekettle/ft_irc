#include "Server.hpp"
#include <csignal>
#include "utils.hpp"

Server*	g_server = NULL;

void	sig_stop(int code) {
	if (code == SIGINT) {
		for (std::map<int, Client*>::iterator it = (g_server->getClients()).begin(); it != (g_server->getClients()).end(); it++) {
			std::cerr << it->first << std::endl;
			g_server->disconnectClient(it->first);
		}
	}
	g_server->stop();
}

int	main(int ac, char** av) {
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
