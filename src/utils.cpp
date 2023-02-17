#include "utils.hpp"

bool	symbolBlackList(std::string	str)
{
	std::string	s = "@,";

	for (size_t i = 0; i < str.length(); i++)
	{
		for (size_t j = 0; j < s.length(); j++)
		{
			if (str[i] == s[j])
				return (false);
		}
	}
	return (true);
}

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
