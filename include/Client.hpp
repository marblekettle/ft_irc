#ifndef FT_IRC_CLIENT_HPP
# define FT_IRC_CLIENT_HPP

# include <iostream>

class Client {

public:

					Client( const std::string & name );
					~Client( ) {}

protected:

private:

	std::string		_name;
};

#endif //FT_IRC_CLIENT_HPP
