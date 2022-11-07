//	Types.hpp : A collection of typedefs of commonly used or wordy datatypes and their required includes

#ifndef TYPES_HPP
# define TYPES_HPP
# include <iostream>		//std::cout, std::string
# include <netinet/in.h>	//inet_ntoa
# include <vector>
# include <queue>			
# include <map>
# include "Client.hpp"

typedef	std::string				t_str;		//String
typedef unsigned int			t_ip;		//IPv4 address stored as int (using htonl())
typedef unsigned short			t_port;		//Port number stored as short (using htons())
typedef struct sockaddr_in		t_addrin;	//Socket address struct, formatted with access to sin_port and sin_addr
typedef struct sockaddr			t_addr;		//Socket address struct used by bind()
typedef struct pollfd			t_fd;		//Struct with file destriptor and event mask used by poll()
typedef std::vector<t_fd>		t_fdv;		//Vector of file descriptors, .data() given to poll()
typedef std::map<int, t_addrin>	t_addrmap;	//Map of file descriptor numbers to address structs
typedef std::pair<int, t_str>	t_datap;	//Pair containing datastream input and corresponding file descriptor
typedef std::queue<t_datap>		t_dataq;	//Queue of data from datastreams
typedef std::pair<int, bool>	t_conn;		//Pair containing a file descriptor, plus true upon opening, false upon disconnect
typedef std::queue<t_conn>		t_connq;	//Queue of established/disconnected connections
typedef std::map<int ,Client*>	t_clients;	//Map of connected client pointer with fd as key
#endif
