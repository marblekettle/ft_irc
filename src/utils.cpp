#include "utils.hpp"


std::string	StringToUpper(std::string toConvert)
{
	std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::toupper);
	return (toConvert);
}

void	logToServer(std::string &message)
{
	time_t ltime;
	struct tm result;
	char stime[32];

	ltime = time(NULL);
	localtime_r(&ltime, &result);
	std::cout << asctime_r(&result, stime) << std::endl;
}