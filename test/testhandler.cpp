#include "Server.hpp"
#include "HandleCommand.hpp"

int	main(int ac, char** av) {
	if (ac == 2) {
		t_str	input(av[1]);
		HandleCommand	hc(NULL);
		hc.call(input, NULL);
		for (size_t i = 0; i < hc.getNArgs(); i++)
			std::cout << i << ": [" << hc.getArg(i) << "]" << std::endl;
	}
	return (0);
}