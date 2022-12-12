#include "utils.hpp"


std::string	StringToUpper(std::string toConvert)
{
	std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::toupper);
	return (toConvert);
}

void	logToServer(std::string &message)
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	std::string str(buffer);
	std::cout << "[" << str << "] " << message << std::endl;
}
