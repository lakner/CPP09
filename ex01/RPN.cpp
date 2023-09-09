#include "RPN.hpp"
#include <array>

bool validate(std::array<char, 21> expression)
{
	if (!isdigit(expression[0]))
		return false;
	for (int i = 1; expression[i]; i +=2 )
	{
		if (!isdigit(expression[i]))
			return false;
	}

	for (int i = 2; expression[i]; i += 2)
	{
		if (expression[i] != '+' && expression[i] !='-'
			&& expression[i] != '*' && expression[i] != '/')
				return false;
	}
	return true;
}