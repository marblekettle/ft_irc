#include "utils.hpp"


std::string	StringToUpper(std::string toConvert)
{
	std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::toupper);
	return (toConvert);
}
