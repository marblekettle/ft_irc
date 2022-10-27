#ifndef TYPES_HPP
# define TYPES_HPP
# include <iostream>
# include <netinet/in.h>
# include <vector>
# include <queue>
# include <map>

typedef	std::string				t_str;
typedef unsigned int			t_ip;
typedef unsigned short			t_port;
typedef struct sockaddr_in		t_addrin;
typedef struct sockaddr			t_addr;
typedef struct pollfd			t_fd;
typedef std::vector<t_fd>		t_fdv;
typedef std::map<int, t_addrin>	t_addrmap;
typedef std::pair<int, t_str>	t_datap;
typedef std::queue<t_datap>		t_dataq;
typedef std::pair<int, bool>	t_conn;
typedef std::queue<t_conn>		t_connq;


#endif
