#include "Server.hpp"
#include <errno.h>

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
				t_datap	data;
				while (1) {
					int a = server.getQueuedData(data);
					if (a == 0)
						break ;
					std::cout << server.getIP(data.first) << ": ";
					std::cout << data.second << std::endl;
				}
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
