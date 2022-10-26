#ifndef FT_IRC_CHANNEL_HPP
# define FT_IRC_CHANNEL_HPP

# include <iostream>
# include <list>
# include <Client.hpp>

class Channel {

public:

						Channel( const std::string & name );
						~Channel( ) {}

	void				join( Client * client );

private:

	std::string			_name;
	std::list<Client *>	_clientList;

};

#endif //FT_IRC_CHANNEL_HPP
