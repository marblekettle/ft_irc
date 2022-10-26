#ifndef TYPES_HPP
# define TYPES_HPP
# include <iostream>
# include <netinet/in.h>
# include <vector>
# include <map>

typedef	std::string				t_str;
typedef unsigned int			t_ip;
typedef unsigned short			t_port;
typedef struct sockaddr_in		t_addrin;
typedef struct sockaddr			t_addr;
typedef struct pollfd			t_fd;
typedef std::vector<t_fd>		t_fdv;

typedef	struct	s_client {
	int		fd;
	t_str	ip;
	char	nick[16];
	bool	reg;
}								t_client;

typedef std::map<int, t_client>	t_cmap;

#endif
