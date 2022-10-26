#include "Server.hpp"
#include <cerrno>

int	main(int ac, char** av) {
	if (ac == 3) {
		t_str	portstr(av[1]);
		t_str	passwd(av[2]);
		if (portstr.find_first_not_of("123467890") != std::string::npos) {
			std::cerr << "Incorrect port number" << std::endl;
			return (0);
		}
		t_port	port = static_cast<t_port>(std::stoi(portstr));
		try {
			Server	server(port, passwd);
			while (1) {
				if (server.pollClients() < 0)
					throw (Server::connectionError());
			}
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	} else {
		std::cerr << "Incorrect arguments" << std::endl;
	}
	std::cerr << strerror(errno) << std::endl;
	return (0);
}
