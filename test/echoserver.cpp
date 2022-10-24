#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>

int	main(void) {
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		std::cerr << "Socket failed" << std::endl;
		return (0);
	}
	fcntl(sock, F_SETFL, O_NONBLOCK);
	struct sockaddr_in	addr;
	bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6667);
	addr.sin_addr.s_addr = htonl(0x7F000001);
	if (bind(sock, reinterpret_cast<struct sockaddr*>(&addr), sizeof(struct sockaddr))) {
		std::cerr << "Bind failed" << std::endl;
		return (0);
	}
	if (listen(sock, 10)) {
		std::cerr << "Error while listening" << std::endl;
		return (0);
	}
	struct pollfd	fds[10];
	fds[0].fd = sock;
	fds[0].events = POLLIN;
	int fdsize = 1;
	while (1) {
		if (poll(fds, fdsize, 1000) == -1) {
			std::cerr << "Poll error" << std::endl;
			return (0);
		}
		for (int i = 1; i < fdsize; i++) {
			if (fds[i].revents & POLLIN) {
				char	buf[2000];
				bzero(buf, 2000);
				if (recv(fds[i].fd, buf, 2000, 0) > 0)
					std::cout << buf << std::endl;
			}
		}
		if (fds[0].revents & POLLIN) {
			struct sockaddr_in	addr;
			socklen_t			asize = sizeof(struct sockaddr_in);
			fds[fdsize].fd = accept(fds[0].fd, reinterpret_cast<struct sockaddr*>(&addr), &asize);
			if (fds[fdsize].fd < 0 || asize != sizeof(struct sockaddr_in)) {
				std::cerr << "Couldn't accept connection" << std::endl;
				return (0);				
			}
			fds[fdsize].events = POLLIN | POLLOUT;
			fdsize++;
		}
	}
	return (0);
}